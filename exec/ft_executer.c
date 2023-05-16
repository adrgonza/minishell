/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:02:09 by amejia            #+#    #+#             */
/*   Updated: 2023/05/16 13:50:09 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_commands(t_token *token)
{
	int	ct;

	ct = 0;
	while (token != NULL)
	{
		if (token->type == T_COMMAND)
			ct++;
		token = token->next;
	}
	return (ct);
}

void	executer_loop_post(int *it, t_token **token)
{
	if (((*token)->type == T_GREATGREAT || (*token)->type == T_GREAT)
		&& !(*token)->processed)
		set_pipeoutput2((*token), &it[2]);
	if ((*token)->type == T_PIPE)
	{
		if (it[2] != -1)
			it[0] = it[2];
		else
			it[0] = 0;
	}
	*token = (*token)->next;
}

int	executer_loop_pre(int *it, t_token **token)
{
	if ((*token)->type == 6 || (*token)->type == 7 || (*token)->type == T_STDIN)
		it[0] = set_pipeinput(*token, &it[2]);
	if (it[0] == -1)
	{
		while (*token && (*token)->type != T_COMMAND)
			*token = (*token)->next;
		if (*token && (*token)->next)
			*token = (*token)->next;
		it[0] = STDIN_FILENO;
		return (1);
	}
	return (0);
}

int	ft_executerloop(t_token *token, int *it, int *id)
{
	while (token)
	{
		if (executer_loop_pre(it, &token) == 1)
			continue ;
		if (token->type == T_COMMAND)
		{
			it[1] = set_pipeoutput(token, &it[2]);
			if (it[1] == -1)
			{
				token = token->next;
				continue ;
			}
			if (it[6] == 1 && check_builtin(token) == 0)
				ft_builtinexec(token);
			else
			{
				id[it[3]] = fork_exec(token, it, id);
				it[3]++;
			}
		}
		executer_loop_post(it, &token);
	}
	return (0);
}

	// int		fdin; 0
	// int		fdout;1
	// int		nextfdin;2
	// int		ct;3
	// int		ct2;4
	// int		*id;
	// int		status; 5
	// int		numb_commands; 6
void	ft_executer(t_token *token)
{
	int	it[7];
	int	*id;

	it[6] = count_commands(token);
	id = ft_calloc(it[6], sizeof(int));
	it[3] = 0;
	it[2] = -1;
	if (ft_executerloop(token, it, id) == -1)
	{
		g_state.last_return = 1;
		free (id);
		return ;
	}
	it[4] = -1;
	while (++it[4] < it[3])
		waitpid(id[it[4]], &it[5], 0);
	if (it[3] > 0)
		g_state.last_return = WEXITSTATUS(it[5]);
	free(id);
}
