/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:42:13 by amejia            #+#    #+#             */
/*   Updated: 2023/05/16 12:46:15 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	more_kid_stuff(int *error, int fdin, int fdout, t_token *token)
{
	g_state.am_child = 1;
	if (fdin != STDIN_FILENO)
	{
		*error = dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		*error = dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	if (check_builtin(token) == 0)
	{
		ft_builtinexec(token);
		exit(g_state.last_return);
	}
	ft_exectkn(token);
}

int	fork_exec(t_token *token, int fdin, int fdout)
{
	int	id;
	int	error;

	error = 0;
	id = fork();
	if (id == 0)
		more_kid_stuff(&error, fdin, fdout, token);
	else
	{
		if (fdin != STDIN_FILENO)
			close(fdin);
		if (fdout != STDOUT_FILENO)
			close(fdout);
	}
	return (id);
}

int	here_doc_prompt(t_token *token)
{
	char	*command;
	int		pip[2];

	pipe(pip);
	while (1)
	{
		command = readline("heredoc (>^.^)> ");
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
	return (pip[0]);
}
