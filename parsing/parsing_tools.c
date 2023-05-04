/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:04:31 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/05 01:41:08 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*variable_expansion(char *cmd, int i)
{
	t_env *data;
	char *var;
	char *expanded_cmd;
	int var_len;
	int args_len;

	//if (cmd[i + 1] == '?')

	if (cmd[i + 1] == '{')
		i++;
	var_len = ++i;
	while (cmd[var_len] && ft_isalnum(cmd[var_len]))
		var_len++;
	var = ft_substr(cmd, i, var_len - i);
	data = ft_envfind(var);
	if (!data)
		var_len = 0;
	else
		args_len = ft_strlen(data->args);
	expanded_cmd = malloc((ft_strlen(cmd) + args_len - (var_len - i) + 3));
	if (!expanded_cmd)
		return(NULL);
	if (cmd[i - 1] == '{')
		i--;
	ft_strlcpy(expanded_cmd, cmd, i++);
	expanded_cmd = ft_strjoin(expanded_cmd, "\"");
	if (data)
		expanded_cmd = ft_strjoin(expanded_cmd, data->args);
	expanded_cmd = ft_strjoin(expanded_cmd, "\"");
	while (cmd[i] && ft_isalnum(cmd[i]))
		i++;
	if (cmd[i] == '}')
		i++;
	var = ft_substr(cmd, i , ft_strlen(cmd) - i);
	expanded_cmd = ft_strjoin(expanded_cmd, var);
	return (expanded_cmd);
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
			if (cmd[i + 1] && (ft_isalnum(cmd[i + 1]) || cmd[i + 1] == '{' || cmd[i + 1] == '?'))
				cmd = variable_expansion(cmd, i--); /* expand each variable */
	}
	if (dbl_quotes % 2 != 0 || smp_quotes % 2 != 0) /* checks if quotes nb is not pair */
		return (perror("syntax error near close quotes\n"), NULL);
	return (cmd);
}

