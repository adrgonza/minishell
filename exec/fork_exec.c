/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:42:13 by amejia            #+#    #+#             */
/*   Updated: 2023/05/16 13:55:01 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	kid_stuff(t_token *token, int *it, int *id)
{
	int	error;

	g_state.am_child = 1;
	if (it[0] != STDIN_FILENO)
	{
		error = dup2(it[0], STDIN_FILENO);
		close(it[0]);
	}
	if (it[1] != STDOUT_FILENO)
	{
		error = dup2(it[1], STDOUT_FILENO);
		close(it[1]);
	}
	close(it[2]);
	if (check_builtin(token) == 0)
	{
		ft_builtinexec(token, id);
		free(id);
		exit(g_state.last_return);
	}
	ft_exectkn(token);
	return (error);
}

int	fork_exec(t_token *token, int *it, int *prev_id)
{
	int	id;
	int	error;

	id = fork();
	if (id == 0)
		error = kid_stuff(token, it, prev_id);
	else
	{
		if (it[0] != STDIN_FILENO)
			close(it[0]);
		if (it[1] != STDOUT_FILENO)
			close(it[1]);
	}
	return (id);
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
		g_state.last_return = 1;
		return (-1);
	}
	return (fdtemp);
}

int	set_pipeoutput(t_token *token, int *nextinput)
{
	int	fdfile;
	int	pip[2];

	token->next->processed = 1;
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
	{
		perror("Minishell");
		g_state.last_return = 1;
	}
	return (fdfile);
}

int	set_pipeoutput2(t_token *token, int *nextinput)
{
	int	fdfile;
	int	pip[2];

	token->processed = 1;
	if (token->type == T_STDOUT)
		fdfile = STDOUT_FILENO;
	if (token->type == T_GREATGREAT)
		fdfile = open(token->args[0], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (token->type == T_GREAT)
		fdfile = open(token->args[0], \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->type == T_PIPE)
	{
		pipe(pip);
		fdfile = pip[1];
		*nextinput = pip[0];
	}	
	if (fdfile == -1)
	{
		perror("Minishell");
		g_state.last_return = 1;
	}
	return (fdfile);
}
