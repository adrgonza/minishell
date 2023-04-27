/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:04:31 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/27 15:38:34 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*p_check_quotes(char *cmd) /* cheks if there is an open quote, semicolon or '\' */
{
	char *path;
	int path_len;
	int count_q;
	int count_simple_q;
	int i;

	count_q = 0;
	count_simple_q = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == ';' && count_simple_q % 2 == 0 && count_q % 2 == 0)
			return (perror("syntax error near unexpected token `;'\n"), NULL);
		if (cmd[i] == '\\' && count_simple_q % 2 == 0 && count_q % 2 == 0)
			return (perror("syntax error near unexpected token `\\'\n"), NULL);
		if (cmd[i] == '"' && (count_simple_q % 2 == 0))
				count_q++;
		if (cmd[i] == '\'' && (count_q % 2 == 0))
				count_simple_q++;
		if (cmd[i] == '$' && count_simple_q % 2 == 0)
		{
			if (cmd[i + 1] != ' ' && cmd[i + 1] != '"' && cmd[i + 1] != '\'')
			{
				i++;
				path_len = i;
				while (cmd[path_len] && cmd[path_len] != ' ' && cmd[path_len] != '"')
					path_len++;
				path = ft_substr(cmd, i, path_len - i);
				ft_envfind(path);
				printf("path: %s", path);
				free(path);
			}
		}
	}
	if (count_q % 2 != 0 || count_simple_q % 2 != 0) /* checks if quotes nb is not pair */
		return (perror("Error, cierra las comillas!!\n"), NULL);
	return (cmd);
}

