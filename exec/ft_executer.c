/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:02:09 by amejia            #+#    #+#             */
/*   Updated: 2023/04/20 22:50:15 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_executer2(int *id, int *ct, int **pip, t_token *token)
{
	pipe_con_before_forks(token, pip, ct[2]);
	while (token != NULL)
	{
		if (token->type == T_COMMAND)
		{
			id[ct[1]] = fork();
			if (id[ct[1]] == 0)
			{
				close(pip[ct[0] - 1][1]);
				close(pip[ct[0]][0]);
				dup2(pip[ct[0] - 1][0], STDIN_FILENO);
				dup2(pip[ct[0]][1], STDOUT_FILENO);
				close(pip[ct[0] - 1][0]);
				close(pip[ct[0]][0]);
				ft_exectkn(token);
			}
			ct[1]++;
		}
		token = token->next;
		ct[0]++;
	}
}

void ft_executer3(int *id, int *ct, int **pip, t_token *token)
{
	
	ct[0] = 0;
	while (ct[0] < ct[2])
	{	
		close(pip[ct[0]][1]);
		close(pip[ct[0]][0]);
		ct[0]++;
	}
	ct[0] = 0;
	while (ct[0] < ct[1])
	{
		waitpid(id[ct[0]], &ct[3], 0);
		ct[0]++;
	}
	free (pip);
	free (id);
	g_state.last_return = ct[3];
}

void	ft_executer(t_token *token)
{
	int **pip;
	int *id;
	int ct[4];
	
	ft_bzero(ct, 3 * sizeof(int));
	ct[2] = pipe_counter(token);
	pip = pipe_generator(ct[2]);
	if (pip == NULL)
		malloc_fail_proc();
	id = ft_calloc(ct[2] + 1, sizeof(int));
	if (id == NULL)
		malloc_fail_proc();
	ft_executer2(id, ct, pip, token);
	ft_executer3(id, ct, pip, token);	
	// add status to global WEXITSTATUS(ct[3]);
}


