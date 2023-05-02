/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:37:06 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/02 17:51:20 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **arrayjoin(char **array1, char ** array2)
{
	char **aux;
	int i;
	int j;

	i = 0;
	j = 0;
	while (array1[i])
		i++;
	while (array2[j])
		j++;
	aux = malloc(sizeof(char*) * (j + i + 1));
	if (!aux)
		return(NULL);
	aux[j + i] = NULL;
	i = -1;
	while (array1[++i])
		aux[i] = ft_strdup(array1[i]);
	j = 0;
	while (array2[j])
		aux[i++] = ft_strdup(array2[j++]);
	i = -1;
	while (array1[++i])
		free(array1[i]);
	free(array1);
	i = -1;
	while (array2[++i])
		free(array2[i]);
	free(array2);
	return (aux);
}

void reordenate_tokens(t_token	**token)
{
	t_token *tmp;
	char **aux;

	tmp = *token;
	while (*token)
	{
		aux = (*token)->args;
		if ((*token)->next && (*token)->type == T_COMMAND)
		{
			*token = (*token)->next;
			if ((*token)->next && (*token)->type == T_LESS)
			{
				*token = (*token)->next;
				if ((*token)->type == T_COMMAND)
				{
					aux = arrayjoin(aux, (*token)->args);
					*token = ft_tknlast(*token);// add back and put freed pointer in the end (problem here)
					free(*token);
				}
			}
		}
		*token = (*token)->next;
	}
	*token = tmp;
	(*token)->args = aux;
}

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
	if (check_stdin(command)) /* Checks if there is a '<' */
		ft_tknadd_back(&token, ft_tknnew(T_STDIN, NULL));
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
	if (check_stdout(command))
		ft_tknadd_back(&token, ft_tknnew(T_STDOUT, NULL));
	//reordenate_tokens(&token);
	return (token);
}




		//ft_print_args(command, type, args);
//system("echo \"\n\"-----------leaks------------\"\n\" && leaks -q minishell | head -5 | tail -1 ");

//system("leaks -q minishell | head -5 | tail -1 ; echo \"\n\"-----------leaks------------\"\n\"");
