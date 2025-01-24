/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:42:13 by amejia            #+#    #+#             */
/*   Updated: 2023/05/25 17:13:44 by adrgonza         ###   ########.fr       */
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
		ft_builtinexec(token);
		free(id);
		exit(g_state.last_return);
	}
	ft_exectkn(token);
	return (error);
}

int	fork_exec(t_token *token, int *it, int *prev_id)
{
	int	id;

	id = fork();
	if (id == 0)
		kid_stuff(token, it, prev_id);
	else
	{
		g_state.status = S_EXECUTINGCH;
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

	if (token->next)
		token->next->processed = 1;
	else
		fdfile = -1;
	if (token->next && token->next->type == T_STDOUT)
		fdfile = STDOUT_FILENO;
	if (token->next && token->next->type == T_GREATGREAT)
		fdfile = open(token->next->args[0], 0x0001 | O_APPEND | O_CREAT, 0644);
	if (token->next && token->next->type == T_GREAT)
		fdfile = open(token->next->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->next && token->next->type == T_PIPE && nextinput != 0)
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
