/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:31:28 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/08 15:19:40 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int next_redict(int type, char *cmd, int i)
{
	if (type == T_GREATGREAT || type == T_LESSLESS)
		i += 2;
	else
		i++;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
	{
		if (cmd[i] && cmd[i] == '"' && cmd[i + 1])
		{
			i++;
			while (cmd[i] && cmd[i]!= '"')
				i++;
		}
		if (cmd[i] && cmd[i] == '\'' && cmd[i + 1])
		{
			i++;
			while (cmd[i] && cmd[i] == '\'')
				i++;
		}
		else
			i++;
	}
	return (i);
}

int next_cmd(char *cmd, int i)
{
	while (cmd[i] && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
	{
		if (cmd[i] && cmd[i] == '"' && cmd[i + 1]) /* checks commands between double quotes */
		{
			i++;
			while (cmd[i] && cmd[i]!= '"')
				i++;
		}
		if (cmd[i] && cmd[i] == '\'' && cmd[i + 1]) /* checks commands between simple quotes */
		{
			i++;
			while (cmd[i] && cmd[i] == '\'')
				i++;
		}
		else
			i++;
	}
	return (i);
}

int next_arg(int type, char *cmd, int i)
{
	if (type == T_PIPE)
		return (i + 1);
	if (type == T_COMMAND)
		return (next_cmd(cmd, i));
	if (type == T_LESS || type == T_GREAT || type == T_LESSLESS || type == T_GREATGREAT)
		return (next_redict(type, cmd, i));
	return (i);
}

char **get_args(int	type, char *command, int i)
{
	char **args;

	if (type == T_PIPE)
		return (NULL);
	if (type == T_COMMAND)
		return (args = get_cmd_args(command, i));
	if (type == T_LESS || type == T_GREAT)
		return (args = get_redict_args(command, i, type));
	if (type == T_LESSLESS || type == T_GREATGREAT)
		return (args = get_redict_args(command, i, type));
	return (args);
}

int	get_type(char *command, int i)
{
	if (command[i] == '|')
		return(T_PIPE);
	if (command[i] == '<')
	{
		if (command[++i] == '<')
			return (T_LESSLESS);
		return (T_LESS);
	}
	if (command[i] == '>')
	{
		if (command[++i] == '>')
			return (T_GREATGREAT);
		return (T_GREAT);
	}
	return (T_COMMAND);
}
