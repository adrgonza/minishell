/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:18:44 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/26 03:21:27 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **get_iredict_args(char *cmd, int i)
{
	char	**args;
	int		word_count;
	int		j;

	j = i + 2;
	word_count = redict_word_count(cmd, j);
	while (cmd[j] && (cmd[j] == ' ' || cmd[j] == '\t'))
		j++;
	args = malloc((sizeof(char *) * word_count));
	if (!args)
		return (NULL);
	if (word_count == 1)
		return (args[0] = NULL, args);
	args[0] = malloc(sizeof(char *) * count_letters(cmd, j));
	if (!args[0])
		return (NULL);
	i = 0;
	while (cmd[j] && cmd[j] != ' ' && cmd[j] != '\t' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
		args[0][i++] = cmd[j++];
	return (args[0][i] = 0, args[1] = NULL, args);
}

char **get_redict_args(char *cmd, int i)
{
	char **args;
	int word_count;
	int j;

	j = i + 1;
	word_count = redict_word_count(cmd, j);
	while (cmd[j] && (cmd[j] == ' ' || cmd[j] == '\t'))
		j++;
	args = malloc((sizeof(char *) * word_count));
	if (!args)
		return (NULL);
	if (word_count == 1)
		return (args[0] = NULL, args);
	args[0] = malloc(sizeof(char *) * count_letters(cmd, i));
	if (!args[0])
		return (NULL);
	i = 0;
	while (cmd[j] && cmd[j] != ' ' && cmd[j] != '\t' && cmd[j] != '|' && cmd[j] != '<' && cmd[j] != '>')
		args[0][i++] = cmd[j++];
	return (args[0][i] = 0, args[1] = NULL, args);
}

char **get_cmd_args(char *cmd, int i) //finish
{
	char **args;
	int j;
	int k;
	int word_count;

	word_count = count_words(cmd, i);
	args = malloc((sizeof(char *) * word_count) + 1);
	if (!args)
		return (printf("Malloc KO.\n"), exit(0), NULL);
	j = 0;
	while (j < word_count)
	{
		args[j] = malloc(sizeof(char) * count_letters(cmd, i) + 1);
		if (!args[j])
			return (NULL);
		args[j][count_letters(cmd, i)] = 0;
		printf("letter :%d\n", count_letters(cmd, i));
		k = 0;
		while(cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == '"')
			{
				i++;
				while (cmd[i] != '"')
				{
					if (cmd[i] == '"')
						i++;
					else
						args[j][k++] = cmd[i++];
				}
				i++;
			}
			if (cmd[i] == '"')
				i++;
			else
				args[j][k++] = cmd[i++]; /* copy */
		}
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t')) /* skip spaces and tabs */
			i++;
		j++;
	}
	args[j] = NULL;
	return (args);
}
