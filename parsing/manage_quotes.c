/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 03:33:02 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/10 20:52:42 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_double_quotes(char *cmd, int *i, char *arg, int *k)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != '"')
	{
		if (cmd[*i] == '"' && (cmd[*(i + 1)] == ' ' || cmd[*(i + 1)] == '\t'))
			return ;
		if (cmd[*i] == '"')
			(*i)++;
		else
			arg[(*k)++] = cmd[(*i)++];
	}
		(*i)++;
}

void	command_simple_quotes(char *cmd, int *i, char *arg, int *k)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\'')
	{
		if (cmd[*i] == '\'' && (cmd[*(i + 1)] == ' ' || cmd[*(i + 1)] == '\t'))
			return ;
		if (cmd[*i] == '\'')
			(*i)++;
		else
			arg[(*k)++] = cmd[(*i)++];
	}
		(*i)++;
}
