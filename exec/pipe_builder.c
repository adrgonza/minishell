/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:42:13 by amejia            #+#    #+#             */
/*   Updated: 2023/04/27 22:01:21 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int fork_exec(t_token *token, int fdin, int *pipeout)
{
	int id;
	int error;

	id = fork();
	if (id == 0)
	{
		dup2(fdin, STDIN_FILENO);
		dup2(pipeout[1], STDOUT_FILENO);
		close(fdin);
		close(pipeout[0]);
		close(pipeout[1]);
		error = ft_exectkn(token);
		if (error == -1)
		{
			perror ("Execution Error");
			return (-1);
		}
	}
	return (id);
}

void	here_doc_prompt(int *pip, t_token *token)
{
	char	*command;

	while (1)
	{
		command = readline("(>^.^)> Here_doc $");
		if (command == NULL)
			break ;
		if (ft_strncmp(command, token->args[0], -1) == 0)
			break ;
		else
		{
			write(pip[1], command, ft_strlen(command));
			write(pip[1], "\n", 1);
		}
		free(command);
		command = NULL;
	}
	close(pip[1]);
}
