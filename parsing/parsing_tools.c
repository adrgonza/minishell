/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:04:31 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/12 18:55:52 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**arrayjoin(char **array1, char **array2)
{
	char	**aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (array1[i++])
		;
	while (array2[j++])
		;
	aux = ft_calloc(sizeof(char *), (j + i + 1));
	if (!aux)
		return (NULL);
	i = -1;
	while (array1[++i])
		aux[i] = ft_strdup(array1[i]);
	j = 0;
	while (array2[j])
		aux[i++] = ft_strdup(array2[j++]);
	i = -1;
	while (array1[++i])
		free(array1[i]);
	free(array1);
	return (aux);
}

int	check_pipes_cmd(t_token *token)
{
	int cmd;
	int pipe;

	pipe = 1;
	cmd = 0;
	while (token->next)
	{
		if (token->type == T_COMMAND)
		{
			cmd = 1;
			pipe = 1;
		}
		if (token->type == T_PIPE)
		{
			if (cmd == 0)
				return (0);
			cmd = 0;
			pipe = 0;
		}
		token = token->next;
	}
	if (pipe == 0)
		return (0);
	return (1);
}

void	reordenate_tokens(t_token	**token)
{
	if (!check_pipes_cmd(*token))
	{
		ft_tknclear(token);
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		g_state.last_return = 258;
		return ;
	}
	while ((*token)->next)
	{
		if ((*token)->next && (*token)->type == T_COMMAND)
		{
			if ((*token)->next->next && ((*token)->next->type == T_GREAT || (*token)->next->type == T_GREATGREAT || (*token)->next->type == T_LESS || (*token)->next->type == T_LESSLESS))
			{
				if ((*token)->next->next->type == T_COMMAND)
				{
					*token = (*token)->next->next;
					if ((*token)->next)
						(*token)->last->next = (*token)->next;
					(*token)->last->last->args
						= arrayjoin((*token)->last->last->args, (*token)->args);
					while ((*token)->last != NULL)
						*token = (*token)->last;
				}
			}
		}
		if ((*token)->next && (*token)->type == T_COMMAND)
		{
			if ((*token)->next->next && ((*token)->next->type == T_LESS || (*token)->next->type == T_LESSLESS))
			{
				ft_tknswap_next(*token);
				while ((*token)->last != NULL)
					*token = (*token)->last;
			}
		}
		if ((*token)->next && ((*token)->type == T_GREAT || (*token)->type == T_GREATGREAT))
		{
			if ((*token)->next->next && (*token)->next->type == T_COMMAND)
			{
				ft_tknswap_next(*token);
				while ((*token)->last != NULL)
					*token = (*token)->last;
			}
		}
		if ((*token)->next)
			*token = (*token)->next;
	}
	while ((*token)->last != NULL)
		*token = (*token)->last;
}

int	check_parsing_errors(char cmd, int s_qte, int d_qte)
{
	if (cmd == ';' && s_qte % 2 == 0 && d_qte % 2 == 0)
		return (ft_putstr_fd("syntax error near unexpected token `;'\n", 2), g_state.last_return = 0, 0);
	if (cmd == '\\' && s_qte % 2 == 0 && d_qte % 2 == 0)
		return (ft_putstr_fd("syntax error near unexpected token `\\'\n", 2), g_state.last_return = 0, 0);
	return (1);
}

char	*expand_tilde(char *cmd, int i, int first)
{
	char	*expanded_cmd;
	t_env	*data;
	int		args_len;

	data = ft_envfind("HOME");
		args_len = 0;
	if (data || data->args)
		args_len = ft_strlen(data->args);
	expanded_cmd = ft_calloc(1, (ft_strlen(cmd) + args_len) + 3);
	if (!expanded_cmd)
		return (NULL);
	expanded_cmd = expansion_tools(cmd, expanded_cmd, ++i, data);
	if (first)
		free(cmd);
	return (expanded_cmd);
}

char	*check_quotes(char *cmd)
{
	int	first;
	int	i;
	int	d_qte;
	int	s_qte;
	int	heredoc;

	first = 0;
	d_qte = 0;
	s_qte = 0;
	heredoc = 0;
	i = -1;
	while (cmd[++i])
	{
		if (!check_parsing_errors(cmd[i], s_qte, d_qte))
			return (NULL);
		if (cmd[i] == '"' && (s_qte % 2 == 0))
				d_qte++;
		if (cmd[i] == '\'' && (d_qte % 2 == 0))
				s_qte++;
		if (cmd[i] && cmd[i] == '~' && cmd[i - 1] && cmd[i - 1] == ' ' && d_qte % 2 == 0 && s_qte % 2 == 0 && (cmd[i + 1] == ' ' || !cmd[i + 1]))
			cmd = expand_tilde(cmd, i--, first++);
		if (cmd[i] == '|' && cmd[i] == '>' && cmd[i] == '<' && d_qte % 2 == 0 && s_qte % 2 == 0)
			heredoc = 0;
		if (cmd[i] == '<' && cmd[i + 1] == '<' && (d_qte % 2 == 0) && (s_qte % 2 == 0))
				heredoc = 1;
		if (cmd[i] == '$' && s_qte % 2 == 0 && heredoc == 0)
			if (cmd[i + 1] && (ft_isalnum(cmd[i + 1]) || cmd[i + 1] == '?'))
				cmd = variable_expansion(cmd, i--, first++);
	}
	if (d_qte % 2 != 0 || s_qte % 2 != 0)
		return (perror("syntax error near close quotes\n"), NULL);
	return (cmd);
}
