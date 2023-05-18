/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:56:25 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/18 21:42:00 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_s(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (0);
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (str);
}

void	reordenate_tools(t_token **tkn)
{
	if ((*tkn)->next && (*tkn)->type == T_COMMAND)
	{
		if ((*tkn)->next->next && ((*tkn)->next->type <= 9
				&& (*tkn)->next->type >= 6))
		{
			if ((*tkn)->next->next->type == T_COMMAND)
			{
				*tkn = (*tkn)->next->next;
				if ((*tkn)->next)
					(*tkn)->last->next = (*tkn)->next;
				(*tkn)->last->last->args
					= arrayjoin((*tkn)->last->last->args, (*tkn)->args);
				ft_first_tkn(tkn);
			}
		}
	}
	if ((*tkn)->next && (*tkn)->type == T_COMMAND)
	{
		if ((*tkn)->next->next && ((*tkn)->next->type == 6
				|| (*tkn)->next->type == 7))
		{
			ft_tknswap_next(*tkn);
			ft_first_tkn(tkn);
		}
	}
}

void	reordenate_tokens(t_token	**tkn)
{
	if (!check_pipes_cmd(*tkn))
	{
		ft_tknclear(tkn);
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		g_state.last_return = 258;
		return ;
	}
	while ((*tkn)->next)
	{
		reordenate_tools(tkn);
		if ((*tkn)->next && ((*tkn)->type == 8 || (*tkn)->type == 9))
		{
			if ((*tkn)->next->next && (*tkn)->next->type == T_COMMAND)
			{
				ft_tknswap_next(*tkn);
				ft_first_tkn(tkn);
			}
		}
		if ((*tkn)->next)
			*tkn = (*tkn)->next;
	}
	ft_first_tkn(tkn);
}

void	check_quotes_if(char **cmd, int *i, int *multi)
{
	if ((*cmd)[(*i)] == '"' && (multi[2] % 2 == 0))
		multi[1]++;
	if ((*cmd)[(*i)] == '\'' && (multi[1] % 2 == 0))
		multi[2]++;
	if ((*cmd)[(*i)] && (*cmd)[(*i)] == '~' && multi[1] % 2 == 0 && multi[2] % 2
		== 0 && (((*i) - 1) < 0 || (*cmd)[(*i) - 1] == ' ') && (!(*cmd)[*i + 1]
		|| (*cmd)[(*i) + 1] == ' ' || (*cmd)[(*i) + 1] == '/'))
		(*cmd) = expand_tilde((*cmd), (*i)--, multi[0]++);
	if ((*i) >= 0 && (*cmd)[*i] && ((*cmd)[*i] == '|' || (*cmd)[(*i)] == '>')
		&& multi[1] % 2 == 0 && multi[2] % 2 == 0)
		multi[3] = 0;
	if ((*i) >= 0 && (*cmd)[(*i)] && (*cmd)[*i] == '<' && (*cmd)[*i + 1]
		&& (*cmd)[*i + 1] == '<' && (multi[1] % 2 == 0) && (multi[2] % 2
		== 0))
		multi[3] = 1;
	if (*i >= 0 && (*cmd)[(*i)] && (*cmd)[(*i)] == '$' && multi[2] % 2 == 0 &&
		multi[3] == 0 && (*cmd)[(*i) + 1]
		&& (ft_isalnum((*cmd)[(*i) + 1]) || (*cmd)[(*i) + 1] == '?'))
	{
		(*cmd) = variable_expansion((*cmd), (*i)--, multi[0]++);
		if (g_state.here_quote == 1)
			(*cmd) = remove_quotes((*cmd), multi[0]);
	}
	g_state.expand = multi[0];
}

char	*check_quotes(char *cmd)
{
	int	i;
	int	multi[4];

	ft_bzero(multi, 4 * sizeof(int));
	i = -1;
	while (cmd[++i])
	{
		if (!check_parsing_errors(cmd[i], multi[2], multi[1]))
			return (NULL);
		check_quotes_if(&cmd, &i, multi);
	}
	if (multi[1] % 2 != 0 || multi[2] % 2 != 0)
		return (perror("syntax error near close quotes\n"), NULL);
	return (cmd);
}
