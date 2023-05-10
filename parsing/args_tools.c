/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:29:44 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/10 12:06:08 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

int	redict_word_count(char *cmd, int i)
{
	int	word_count;

	word_count = 2;
	if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>' || !cmd[i])
		word_count = 1;
	return (word_count);
}

int	count_words(char *cmd, int i)
{
	int	command_count;

	command_count = 0;
	while (cmd[i] && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
	{
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
		{
			if (cmd[i] == '"')
			{
				i++;
				while (cmd[i] != '"')
					i++;
			}
			if (cmd[i] == '\'')
			{
				i++;
				while (cmd[i] != '\'')
					i++;
			}
			i++;
		}
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		command_count++;
	}
	return (command_count);
}

int	count_letters(char *cmd, int i)
{
	int	j;

	j = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd [i] && cmd[i] != '"')
			{
				i++;
				j++;
			}
			j -= 1;
		}
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd [i] && cmd[i] != '\'')
			{
				i++;
				j++;
			}
			j -= 1;
		}
		j++;
		i++;
	}
	return (j);
}
