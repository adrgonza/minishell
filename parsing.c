/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/24 14:32:13 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	p_get_type(char *command, int i) //finish
{
	if (command[i] == '|')
		return(T_PIPE);
	if (command[i] == ';')
		return (T_SEMICOLON);
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

char **get_args(int	type, char *command, int i)
{
	char **args;

	if (type == T_COMMAND)
		return (args = get_cmd_args(command, i));
	if (type == T_SEMICOLON || type == T_PIPE)
		return (NULL);
	if (type == T_LESS || type == T_GREAT)
	{
		args[0] = &command[i];
		args[1] = NULL;
	}
	if (type == T_LESSLESS || type == T_GREATGREAT)
	{
		args[0] = &command[i];
		args[1] = NULL;
	}
	return (args);
}

int next_arg(int type, char *cmd, int i) //finish
{
	if (type == T_COMMAND)
	{
		while (cmd[i])
		{
			if (cmd[i] == ';' || cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
				return (i);
			i++;
		}
		return (i);
	}
	if ((type == T_SEMICOLON || type == T_PIPE || type == T_LESS || type == T_GREAT))
		return (i + 1);
	if ((type == T_LESSLESS || type == T_GREATGREAT))
		return (i + 2);
	return (i);
}

int p_check_quotes(char *command) //finish
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
	int		type;
	int		i;

	i = 0;
	if (!command[i] || !p_check_quotes(command)) /* Checks if there is not open quotes. */
		return (token);
	if (check_stdin(command)) /* Checks if there is a '<' */
		ft_tknadd_back(&token, ft_tknnew(T_STDIN, NULL));
	while (command[i])
	{
		while (command[i] && (command[i] == ' ' || command[i] == '\t'))
			i++;
		type = p_get_type(command, i);
		args = get_args(type, command, i);
		ft_tknadd_back(&token, ft_tknnew(type, args));
		i = next_arg(type, command, i);
		ft_free_args(args);
	}
	if (check_stdout(command))
		ft_tknadd_back(&token, ft_tknnew(T_STDOUT, NULL));
	return (token);
}

