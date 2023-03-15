/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:43:25 by amejia            #+#    #+#             */
/*   Updated: 2023/03/15 17:22:05 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*

15 march
change get_next_lie for readline
removed tmp (readline fix it)
added command history

*/

void	prompt(char **envp)
{
	char	*command;
	int		id;
	int		status;

	command = (char *)1;
	while (command != NULL)
	{
		command = readline("(>\'-\')>");
		if (command == NULL)
			break ;
		add_history(command);
		id = fork();
		if (id == 0)
			ft_execchar(command, envp);
		else
			waitpid(id, &status, 0);
		if (command != NULL)
			free(command);
	}
}
