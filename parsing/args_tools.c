/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:29:44 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/17 23:51:45 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	jump_quotes_count_words(char *cmd, int i)
{
	if (cmd[i] == '"')
	{
		i++;
		while (cmd[i] && cmd[i] != '"')
			i++;
	}
	if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] && cmd[i] != '\'')
			i++;
	}
	return (i);
}

int	count_words(char *cmd, int i)
{
	int	command_count;

	command_count = 0;
	while (cmd[i] && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
	{
		while (cmd[i] && cmd[i] != ' ' && cmd[i]
			!= '\t' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
		{
			i = jump_quotes_count_words(cmd, i);
			i++;
		}
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		command_count++;
	}
	return (command_count);
}

void	jump_quotes_count_letters(char *cmd, int *i, int *j)
{
	if (cmd[*i] == '"')
	{
		(*i)++;
		while (cmd [*i] && cmd[*i] != '"')
		{
			(*i)++;
			(*j)++;
		}
		*j -= 1;
	}
	if (cmd[*i] == '\'')
	{
		(*i)++;
		while (cmd [*i] && cmd[*i] != '\'')
		{
			(*i)++;
			(*j)++;
		}
		*j -= 1;
	}
}

int	count_letters(char *cmd, int i)
{
	int	j;

	j = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i]
		!= '\t' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
	{
		jump_quotes_count_letters(cmd, &i, &j);
		j++;
		i++;
	}
	return (j);
}
