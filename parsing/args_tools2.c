/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:54:17 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/17 21:55:00 by adrgonza         ###   ########.fr       */
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
