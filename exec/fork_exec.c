/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:42:13 by amejia            #+#    #+#             */
/*   Updated: 2023/04/29 22:54:40 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	kid_stuff(t_token *token, int *fdin, int *fdout, int *error)
{
	g_state.am_child = 1;
	if (*fdin != STDIN_FILENO)
	{
		*error = dup2(*fdin, STDIN_FILENO);
		close(*fdin);
	}
	if (*fdout != STDOUT_FILENO)
	{
		*error = dup2(*fdout, STDOUT_FILENO);
		close(*fdout);
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

	id = fork();
	if (id == 0)
		kid_stuff(token, &fdin, &fdout, &error);
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
	return (pip[0]);
}

int	set_pipeinput(t_token *token, int *nextfdin)
{
	int	fdtemp;

	fdtemp = -1;
	if (token->last != NULL && *nextfdin != -1)
	{
		close(*nextfdin);
		*nextfdin = -1;
	}
	if (token->type == T_STDIN)
		fdtemp = STDIN_FILENO;
	if (token->type == T_LESS)
		fdtemp = open(token->args[0], O_RDONLY);
	if (token->type == T_LESSLESS)
		fdtemp = here_doc_prompt(token);
	if (fdtemp == -1)
	{
		perror("Minishell");
		return (-1);
	}
	return (fdtemp);
}

int	set_pipeoutput(t_token *token, int *nextinput)
{
	int	fdfile;
	int	pip[2];

	if (token->next->type == T_STDOUT)
		fdfile = STDOUT_FILENO;
	if (token->next->type == T_GREATGREAT)
		fdfile = open(token->next->args[0], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (token->next->type == T_GREAT)
		fdfile = open(token->next->args[0], \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->next->type == T_PIPE)
	{
		pipe(pip);
		fdfile = pip[1];
		*nextinput = pip[0];
	}	
	if (fdfile == -1)
		perror("Minishell");
	return (fdfile);
}
