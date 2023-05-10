/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:04:31 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/10 16:13:44 by adrgonza         ###   ########.fr       */
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

void	reordenate_tokens(t_token	**token)
{
	t_token	*first;

	first = *token;
	while ((*token)->next)
	{
		if ((*token)->next && (*token)->type == T_COMMAND)
		{
			*token = (*token)->next;
			if ((*token)->next && ((*token)->type == 6 || (*token)->type == 8
					|| (*token)->type == 7 || (*token)->type == 9))
			{
				*token = (*token)->next;
				if ((*token)->type == T_COMMAND)
				{
					if ((*token)->next)
						(*token)->last->next = (*token)->next;
					(*token)->last->last->args
						= arrayjoin((*token)->last->last->args, (*token)->args);
				}
			}
		}
		else if ((*token)->next)
			*token = (*token)->next;
	}
	*token = first;
}

int	check_parsing_errors(char cmd, int s_qte, int d_qte)
{
	if (cmd == ';' && s_qte % 2 == 0 && d_qte % 2 == 0)
		return (perror("syntax error near unexpected token `;'\n"), 0);
	if (cmd == '\\' && s_qte % 2 == 0 && d_qte % 2 == 0)
		return (perror("syntax error near unexpected token `\\'\n"), 0);
	return (1);
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
		if (cmd[i] == '|' && cmd[i] == '>' && d_qte % 2 == 0 && s_qte % 2 == 0)
			heredoc = 0;
		if (cmd[i] == '<' && (d_qte % 2 == 0) && (s_qte % 2 == 0))
		{
			heredoc = 0;
			if (cmd[++i] == '<')
				heredoc = 1;
		}
		if (cmd[i] == '$' && s_qte % 2 == 0 && heredoc == 0)
			if (cmd[i + 1] && (ft_isalnum(cmd[i + 1]) || cmd[i + 1] == '?'))
				cmd = variable_expansion(cmd, i--, first++);
	}
	if (d_qte % 2 != 0 || s_qte % 2 != 0)
		return (perror("syntax error near close quotes\n"), NULL);
	return (cmd);
}
