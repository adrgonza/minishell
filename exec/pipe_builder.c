/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:42:13 by amejia            #+#    #+#             */
/*   Updated: 2023/05/11 21:13:59 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int fork_exec(t_token *token, int fdin, int fdout)
{
	int id;
	int error;

	id = fork();
	if (id == 0)
	{
		g_state.am_child = 1;
		if (fdin != STDIN_FILENO)
		{
			error = dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		if (fdout != STDOUT_FILENO)
		{
			error = dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		if (check_builtin(token) == 0)
		{
			ft_builtinexec(token);
			exit(g_state.last_return);
		}
		ft_exectkn(token);
	}
	else
	{
		if (fdin != STDIN_FILENO)
			close(fdin);
		if (fdout != STDOUT_FILENO)
			close(fdout);
	}
	return (id);
}

int here_doc_prompt(t_token *token)
{
	char *command;
	int pip[2];

	pipe(pip);
	while (1)
	{
		command = readline("heredoc (>^.^)>");
		if (command == NULL)
			break;
		if (ft_strncmp(command, token->args[0], -1) == 0)
			break;
		else
		{
			write(pip[1], command, ft_strlen(command));
			write(pip[1], "\n", 1);
		}
		free(command);
		command = NULL;
	}
	close(pip[1]);
	return (pip[0]);
}
