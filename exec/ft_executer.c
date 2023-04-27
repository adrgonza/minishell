/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:02:09 by amejia            #+#    #+#             */
/*   Updated: 2023/04/27 22:28:57 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void set_pipeinput(t_token *token, int *pip, int *fd)
{
	pipe(pip);
	if (token->last->type == T_STDIN)
		pip[1] = dup(STDIN_FILENO);
	if (token->last->type == T_LESS)
		pip[1] = open(token->args[0],O_RDONLY);
	if (token->last->type == T_LESSLESS)
		here_doc_prompt(pip,token->last);
	close(pip[1]);
	*fd = pip[0];
}


void	ft_executer(t_token *token)
{
	int pip[2];
	int fdread;
	int ct;
	int *id;
	
	id = ft_calloc(ft_tknsize(token),sizeof(int));
	fdread = -1;
	ct = 0;
	redirect_order_sort(token);
	while (token)
	{
		if (token->type == T_LESS || token->type == T_LESSLESS 
				|| token->type == T_STDIN)
			set_pipeinput(token, pip, &fdread);
		if (token->type == T_COMMAND)
		{
			pipe(pip);
			id[ct] = fork_exec(token, fdread, pip);
			ct++;
		}
	}	
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