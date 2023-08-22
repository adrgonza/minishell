/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:56:25 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/24 00:59:23 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reordenate_tools2(t_token **tkn)
{
	if ((*tkn)->next && (*tkn)->type == T_COMMAND)
	{
		if ((*tkn)->next->next && ((*tkn)->next->type == 6
				|| (*tkn)->next->type == 7))
		{
			ft_tknswap_next(*tkn);
			ft_first_tkn(tkn);
			return ;
		}
	}
}

void	reordenate_tools(t_token **tkn)
{
	t_token	*tk;

	if ((*tkn)->next && (*tkn)->type == T_COMMAND)
	{
		if ((*tkn)->next->next && ((*tkn)->next->type <= 9
				&& (*tkn)->next->type >= 6))
		{
			if ((*tkn)->next->next && (*tkn)->next->next->type == T_COMMAND)
			{
				*tkn = (*tkn)->next->next;
				(*tkn)->last->last->args
					= arrayjoin((*tkn)->last->last->args, (*tkn)->args);
				tk = *tkn;
				if ((*tkn)->next)
				{
					(*tkn)->last->next = (*tkn)->next;
					(*tkn)->next->last = (*tkn)->last;
				}
				ft_first_tkn(tkn);
				ft_tkndelone(tk);
				return ;
			}
		}
	}
}

void	reordenate_tokens(t_token	**tkn)
{
	if (!check_pipes_cmd(*tkn) || !check_redict_arg(*tkn))
	{
		ft_tknclear(tkn);
		g_state.last_return = 258;
		return ;
	}
	while ((*tkn)->next)
	{
		reordenate_tools(tkn);
		reordenate_tools2(tkn);
		if ((*tkn)->next && ((*tkn)->type == 8 || (*tkn)->type == 9))
		{
			if ((*tkn)->next->next && (*tkn)->next->type == T_COMMAND)
			{
				ft_tknswap_next(*tkn);
				ft_first_tkn(tkn);
			}
		}
		if ((*tkn)->next && (*tkn)->next->type == 1)
			return (ft_first_tkn(tkn));
		if ((*tkn)->next)
			*tkn = (*tkn)->next;
	}
	ft_first_tkn(tkn);
}

void	check_quotes_if(char **cmd, int *i, int *multi)
{
	if ((*i) >= 0 && (*cmd)[(*i)] && (*cmd)[*i] == '<' && (*cmd)[*i + 1]
		&& (*cmd)[*i + 1] == '<' && (multi[1] % 2 == 0) && (multi[2] % 2
		== 0))
		multi[3] = 1;
	if ((*cmd)[(*i)] && (*cmd)[*i] == '~' && multi[1] % 2 == 0 && multi[2] % 2
		== 0 && (((*i) - 1) < 0 || (*cmd)[*i - 1] == ' ') && (!(*cmd)[*i + 1]
		|| (*cmd)[(*i) + 1] == ' ' || (*cmd)[(*i) + 1] == '/') && multi[3] == 0)
			(*cmd) = expand_tilde((*cmd), (*i), multi[0]++);
	if ((*cmd)[(*i)] && (*cmd)[(*i)] == '"' && (multi[2] % 2 == 0))
		multi[1]++;
	if ((*cmd)[(*i)] && (*cmd)[(*i)] == '\'' && (multi[1] % 2 == 0))
		multi[2]++;
	if ((*i) >= 0 && (*cmd)[*i] && ((*cmd)[*i] == '|' || (*cmd)[(*i)] == '>')
		&& multi[1] % 2 == 0 && multi[2] % 2 == 0)
		multi[3] = 0;
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
		if (!check_parsing_errors(cmd, multi[2], multi[1], i))
			return (NULL);
		check_quotes_if(&cmd, &i, multi);
	}
	if (multi[1] % 2 != 0 || multi[2] % 2 != 0)
	{
		g_state.last_return = 0;
		return (ft_putstr_fd("Syntax error near close quotes.\n", 2), NULL);
	}
	return (cmd);
}
