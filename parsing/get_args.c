/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:18:44 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/18 01:00:36 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		k = 0;
		while(cmd[i] && cmd[i] != ' ')
		{
			args[j][k++] = cmd[i++]; /* copy */
			if (cmd[i] == ';' || cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
				return (args[++j] = NULL, args);
		}
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		j++;
	}
	args[j] = NULL;
	return (args);
}
