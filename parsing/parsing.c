/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/14 17:23:43 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*p_get_type(char *command, int i)
{
	if (command[i] == '|')
		return("PIPE");
	if (command[i] == '<')
	{
		if (command[++i] == '<')
			return ("LESSLESS");
		return ("LESS");
	}
	if (command[i] == '>')
	{
		if (command[++i] == '>')
			return ("GREATGREAT");
		return ("GREAT");
	}
	if (command[i] == ';')
		return ("SEMICOLON");
	return ("COMMAND");
}

int p_check_quotes(char *command)
{
	int i;
	int count_q;
	int count_simple_q;

	count_q = 0;
	count_simple_q = 0;
	i = -1;
	while (command[++i])
	{
		if (command[i] == '"' && (count_simple_q % 2 == 0))
			if (i == 0 || (command[i - 1] != '\\' || command[i - 2] == '\\'))
				count_q++;
		if (command[i] == '\'' && (count_q % 2 == 0))
			if (i == 0 || (command[i - 1] != '\\' || command[i - 2] == '\\'))
				count_simple_q++;
	}
	if (count_q % 2 != 0 || count_simple_q % 2 != 0) /* checks if quotes nb is not pair */
		return (printf("Error, cierra las comillas!!\n"), 0);
	return (1);
}

t_token	*parsing(char *command)
{
	t_token *token = NULL;
	char	**args;
	char	*type;
	int i;

	if (!p_check_quotes(command)) /* Checks if there is not open quotes. */
		return (token);
	/*ft_tkn_new();
	i = -1;
	while (command[++i])
	{
		while (command[i] == ' ')  jump spaces
			i++;
		type = ft_get_type(command, i);  gets de type of the fisrt token
		args
		ft_tkn_add_back(token, ft_tkn_new(type, args));
	}*/
	return (token);
}
