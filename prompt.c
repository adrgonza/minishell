/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:43:25 by amejia            #+#    #+#             */
/*   Updated: 2023/03/14 14:49:03 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **envp)
{
	char	*command;
	char 	*tmp;
	int		id;
	int		status; 
	
	command = (char *)1;
	while (command != NULL)
	{	
		ft_printf("(>\'-\')>");
		command = get_next_line(2);
		if (command == NULL)
			break ;
		tmp = ft_strchr(command, '\n');
		*tmp = '\0';
		id = fork();
		if (id == 0) 
			ft_execchar(command,envp);
		else 
			waitpid(id,&status,0);
		if (command != NULL)
			free(command);
	}
}