/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/28 02:22:22 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_print_args(char *cmd, int type, char **args)
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
	t_token	*token = NULL;
	char	**args;
	int		type;
	int		i;

	command = check_quotes(command); /* checks if there is any open quote and expand variables */
	if (!command)
		return (token);
	i = 0;
	while (command[i])
	{
		while (command[i] && command[i] == ' ') /* jump spaces */
			i++;
		type = get_type(command, i); /* get the type  */
		args = get_args(type, command, i); /* get the argumments */
		ft_tknadd_back(&token, ft_tknnew(type, args)); /* put values in the list */
		ft_free_args(args); /* free argumments */
		i = next_arg(type, command, i); /* jump to the next argument */
	}
	exit (0);
	//token = reordenate_tokens(token);
	return (token);
}




//ft_print_tkn(command, type, args);
//system("echo \"\n\"-----------leaks------------\"\n\" && leaks -q minishell | head -5 | tail -1 ");

//system("leaks -q minishell | head -5 | tail -1 ; echo \"\n\"-----------leaks------------\"\n\"");
