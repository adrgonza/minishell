/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:04:31 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/09 02:10:55 by adrgonza         ###   ########.fr       */
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
		;;
	while (array2[j++])
		;;
	aux = ft_calloc(sizeof(char *), (j + i + 1));
	if (!aux)
		return(NULL);
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

void reordenate_tokens(t_token	**token)
{
	t_token *first;

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
					(*token)->last->last->args =
					arrayjoin((*token)->last->last->args, (*token)->args);
				}
			}
		}
		else if ((*token)->next)
			*token = (*token)->next;
	}
	*token = first;
}

int check_parsing_errors(char cmd, int smp_quotes, int dbl_quotes)
{
	if (cmd == ';' && smp_quotes % 2 == 0 && dbl_quotes % 2 == 0)
			return (perror("syntax error near unexpected token `;'\n"), 0);
	if (cmd == '\\' && smp_quotes % 2 == 0 && dbl_quotes % 2 == 0)
			return (perror("syntax error near unexpected token `\\'\n"), 0);
	return (1);
}

char	*check_quotes(char *cmd)
{
	int	first;
	int	i;
	int	dbl_quotes;
	int	smp_quotes;
	int	heredoc;

	first = 0;
	dbl_quotes = 0;
	smp_quotes = 0;
	heredoc = 0;
	i = -1;
	while (cmd[++i])
	{
		if (!check_parsing_errors(cmd[i], smp_quotes, dbl_quotes)) /* checks parsing erros */
			return (NULL);
		if (cmd[i] == '"' && (smp_quotes % 2 == 0))
				dbl_quotes++;
		if (cmd[i] == '\'' && (dbl_quotes % 2 == 0))
				smp_quotes++;
		if (cmd[i] == '|' && cmd[i] == '>' && (dbl_quotes % 2 == 0) && (smp_quotes % 2 == 0))
			heredoc = 0;
		if (cmd[i] == '<' && (dbl_quotes % 2 == 0) && (smp_quotes % 2 == 0))
		{
			heredoc = 0;
			if (cmd[++i] == '<')
			{
				heredoc = 1;
				i++;
			}
		}
		if (cmd[i] == '$' && smp_quotes % 2 == 0 && heredoc == 0) /* checks if there is any varible to expand */
			if (cmd[i + 1] && (ft_isalnum(cmd[i + 1]) || cmd[i + 1] == '?'))
				cmd = variable_expansion(cmd, i--, first++); /* expand each variable */
	}
	if (dbl_quotes % 2 != 0 || smp_quotes % 2 != 0) /* checks if quotes nb is not pair */
		return (perror("syntax error near close quotes\n"), NULL);
	return (cmd);
}
