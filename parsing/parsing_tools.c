/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:04:31 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/02 17:52:59 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*variable_expansion(char *cmd, int i)
{
	char *path;
	char *expanded_cmd;
	int path_len;

	path_len = ++i;
	while (cmd[path_len] && cmd[path_len] != ' ' && cmd[path_len] != '"')
		path_len++;
	path = ft_substr(cmd, i, path_len - i);
	ft_envfind(path);
	printf("path: %s", path);
	free(path);
	return (cmd);
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
	int dbl_quotes;
	int smp_quotes;
	int i;

	dbl_quotes = 0;
	smp_quotes = 0;
	i = -1;
	while (cmd[++i])
	{
		if (!check_parsing_errors(cmd[i], smp_quotes, dbl_quotes)) /* checks parsing erros */
			return (NULL);
		if (cmd[i] == '"' && (smp_quotes % 2 == 0))
				dbl_quotes++;
		if (cmd[i] == '\'' && (dbl_quotes % 2 == 0))
				smp_quotes++;
		if (cmd[i] == '$' && smp_quotes % 2 == 0) /* checks if there is any varible to expand */
			if (cmd[i + 1] != ' ' && cmd[i + 1] != '"' && cmd[i + 1] != '\'')
				cmd = variable_expansion(cmd, i); /* expand each variable */
	}
	if (dbl_quotes % 2 != 0 || smp_quotes % 2 != 0) /* checks if quotes nb is not pair */
		return (perror("syntax error near close quotes\n"), NULL);
	return (cmd);
}

