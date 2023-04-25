/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:29:44 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/25 14:30:15 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redict_word_count(char *cmd, int i)
{
	int word_count;

	word_count = 2;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>' || !cmd[i])
		word_count = 1;
	return (word_count);
}

void ft_free_args(char **args) //finish
{
	int i;

	i = -1;
	if (!args)
		return ;
	while (args[++i])
		free(args[i]);
	free(args);
}

int count_words(char *cmd, int i) //finish
{
	int	command_count;

	command_count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
			return (command_count);
		while (cmd[i] && cmd[i] != ' ' && ft_isprint(cmd[i]))
		{
			if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
				return (command_count + 1);
			i++;
		}
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		command_count++;
	}
	return (command_count);
}

int	count_letters(char *cmd, int i) //finish
{
	int j;

	j = 0;
	while (cmd[j] && cmd[j] != ' ' && cmd[j] != '\t' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
	{
		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>' || cmd[i] == ' ')
				return (j);
		j++;
		i++;
	}
	return (j);
}
