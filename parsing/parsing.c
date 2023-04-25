/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/25 14:35:12 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int next_arg(int type, char *cmd, int i) //finish
{
	if (type == T_COMMAND)
	{
		while (cmd[i])
		{
			if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
				return (i);
			i++;
		}
		return (i);
	}
	if (type == T_PIPE)
		return (i + 1);
	if  (type == T_LESS || type == T_GREAT)
	{
		i++;
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
			return (i);
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
			i++;
		return (i);
	}
	if ((type == T_LESSLESS || type == T_GREATGREAT))
	{
		i += 2;
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
			return (i);
		while (cmd[i] && (cmd[i] != ' ' && cmd[i] != '\t'))
			i++;
		return (i);
	}
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
		return (args = get_redict_args(command, i));
	if (type == T_LESSLESS || type == T_GREATGREAT)
		return (args = get_iredict_args(command, i));
	return (args);
}

int	p_get_type(char *command, int i) //finish
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

void ft_print_tkn(char *cmd, int type, char **args)
{
	int i;

	i = 0;
	printf("\n----------------------------\n");
	if (type == 3)
		printf("   type ==> {[Command]}   \n");
	if (type == 4)
		printf("   type ==> {[Pipe]}   \n");
	if (type == 6)
		printf("   type ==> {[LESS]}   \n");
	if (type == 7)
		printf("   type ==> {[LESSLESS]}   \n");
	if (type == 8)
		printf("   type ==> {[GREAT]}   \n");
	if (type == 9)
		printf("   type ==> {[GREATGREAT]}   \n");
	if (type == 4)
	{
		printf("   args(%d) ==> {[%s]}   \n", i, args);
	}
	else
	{
		while(args[i])
		{
			printf("   args(%d) ==> {[%s]}   \n", i, args[i]);
			i++;
		}
		printf("   args(%d) ==> {[%s]}   \n", i, args[i]);
	}
	printf("----------------------------\n\n");
}

t_token	*parsing(char *command)
{
	t_token *token = NULL;
	char	**args;
	int		type;
	int		i;

	system("echo \"\n\"-----------leaks------------\"\n\" && leaks -q minishell | head -5 | tail -1 ");
	i = 0;
	if (!command[i] || !p_check_quotes(command)) /* Checks if there is not open quotes. */
		return (token);
	//command = expand_variables(command);
	if (check_stdin(command)) /* Checks if there is a '<' */
		ft_tknadd_back(&token, ft_tknnew(T_STDIN, NULL));
	while (command[i])
	{
		while (command[i] && (command[i] == ' ' || command[i] == '\t'))
			i++;
		type = p_get_type(command, i);
		args = get_args(type, command, i);
		ft_tknadd_back(&token, ft_tknnew(type, args));
		ft_print_tkn(command, type, args);
		ft_free_args(args);
		i = next_arg(type, command, i);
	}
	if (check_stdout(command))
		ft_tknadd_back(&token, ft_tknnew(T_STDOUT, NULL));
	system("leaks -q minishell | head -5 | tail -1 ; echo \"\n\"-----------leaks------------\"\n\"");
	return (token);
}

