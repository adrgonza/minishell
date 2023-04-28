/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:02:09 by amejia            #+#    #+#             */
/*   Updated: 2023/04/26 23:45:45 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_executer2(int *id, int *ct, int **pip, t_token *token)
{
	pipe_con_before_forks(token, pip, ct[2]);
	while (token != NULL)
	{
		while (token->type == T_PIPE)
			token = token->next;
		if (token->type == T_COMMAND && check_builtin(token, ct[2]) == 1)
		{
			id[ct[1]] = fork();
			if (id[ct[1]] == 0)
			{
				dup2(pip[ct[0] - 1][0], STDIN_FILENO);
				dup2(pip[ct[0]][1], STDOUT_FILENO);
				ct[0] = 0;
				while (ct[0] < ct[2])
				{	
					close(pip[ct[0]][1]);
					close(pip[ct[0]][0]);
					ct[0]++;
				}
				ft_exectkn(token);
			}
			ct[1]++;
		}
		else if (token->type == T_COMMAND)
		{
			id[ct[1]] = 256;
			ft_builtinexec(token);
		}
		ct[0]++;
		token = token->next;
	}
}

void	ft_executer3(int *id, int *ct, int **pip, t_token *token)
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
		if (id[ct[0]] == -1)
			ct[3] = 0;
		else
			waitpid(id[ct[0]], &ct[3], 0);
		ct[0]++;
	}
	free (pip);
	free (id);
	if (ct[3] < 256)
		g_state.last_return = WEXITSTATUS(ct[3]);
	else
		g_state.last_return = 0;
}

void	ft_executer(t_token *token)
{
	int **pip;
	int	*id;
	int	ct[4];
	
	if (token == NULL)
		return ;
	ft_bzero(ct, 3 * sizeof(int));
	ct[2] = pipe_counter(token);
	pip = pipe_generator(ct[2]);
	if (pip == NULL)
		malloc_fail_proc();
	id = ft_calloc(ct[2] - 1, sizeof(int));
	if (id == NULL)
	{
		free(pip);
		malloc_fail_proc();
	}
	token = redirect_check(token);
	ft_executer2(id, ct, pip, token);
	ft_executer3(id, ct, pip, token);	
}

t_token *redirect_order_sort(t_token *token)
{
	t_token *start;

	start = token;
	while((token) != NULL)
	{
		while ((token->type == T_LESS || token->type == T_LESSLESS || token->
			type == T_STDIN) && token->last != 0 && token->last->type != T_PIPE)
			ft_tknswap_last(token);
		token = (token)->next;
	}
	token = start;
	while (token->last != NULL)
		token = token->last;
	while((token->next) != NULL)
	{
		while (((token)->type == T_GREAT || (token)->type == T_GREATGREAT 
			|| (token)->type == T_STDOUT) && (token)->next != NULL 
			&& (token)->next->type != T_PIPE)
			ft_tknswap_next(token);
		if (token->next != NULL)
			token = (token)->next;
	}
	while (token->last != NULL)
		token = token->last;
	return (token);
}

t_token *redirect_check(t_token *token)
{
	t_token *first;
	t_token *end;
	t_token *newtkn;
	
	token = redirect_order_sort(token);
	end = ft_tknlast(token);
	if (token->type != T_STDIN && token->type != T_LESS && token->type \
		!= T_LESSLESS)
		{
			newtkn = ft_tknnew(T_STDIN,NULL);
			if (newtkn == NULL)
				malloc_fail_proc();
			ft_tknadd_front(&token,newtkn);
		}
	if (end->type != T_STDOUT && end->type != T_GREAT && end->type \
		!= T_GREATGREAT)
		{
			newtkn = ft_tknnew(T_STDOUT, NULL);
			if (newtkn == NULL)
				malloc_fail_proc();
			ft_tknadd_back(&token,newtkn);
		}
	return (token);
}