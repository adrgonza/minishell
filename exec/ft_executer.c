/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:02:09 by amejia            #+#    #+#             */
/*   Updated: 2023/04/29 02:42:09 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void print_open_fds() {
    int max_fd = getdtablesize();
    int fd;

    for (fd = 0; fd < max_fd; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("File descriptor %d is open\n", fd);
        }
    }
}

int set_pipeinput(t_token *token, int *nextfdin)
{
	int fdtemp;
	
	fdtemp = -1;
	
	if (token->last != NULL && *nextfdin != -1)
	{
		close(*nextfdin);
		*nextfdin = -1;	
	}
	if (token->type == T_STDIN)
		fdtemp = STDIN_FILENO;
	if (token->type == T_LESS)
		fdtemp = open(token->args[0],O_RDONLY);
	if (token->type == T_LESSLESS)
		fdtemp = here_doc_prompt(token);
	return(fdtemp);
}

int set_pipeoutput(t_token *token, int *nextinput)
{
	int fdfile;
	int pip[2];
	
	if (token->next->type == T_STDOUT)
		fdfile = STDOUT_FILENO;
	if (token->next->type == T_GREATGREAT)
		fdfile = open(token->next->args[0], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (token->next->type == T_GREAT)
		fdfile = open(token->next->args[0], \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if	(token->next->type == T_PIPE)
	{
		pipe(pip);
		fdfile = pip[1];
		*nextinput = pip[0];
	}	
	return (fdfile);
}

void	ft_executer(t_token *token)
{
	int fdin;
	int fdout;
	int nextfdin;
	int ct;
	int ct2;
	int *id;
	
	char *test;
	int	status;

	id = ft_calloc(ft_tknsize(token),sizeof(int));
	nextfdin = -1;
	ct = 0;
	redirect_order_sort(token);
	//print_open_fds();
	//printf("____________________-");
	while (token)
	{
		if (token->type == T_LESS || token->type == T_LESSLESS 
				|| token->type == T_STDIN)
			{
			fdin =set_pipeinput(token,&nextfdin);
			// test = (char *)1;
			// while (test)
			// 	test = get_next_line(fdin);
			 }
		if (token->type == T_COMMAND)
		{
			fdout = set_pipeoutput(token, &nextfdin);
			//write(fdout,"Baby",4);
			//print_open_fds();
			id[ct] = fork_exec(token, fdin, fdout);
			ct++;
		}
		if (token->type == T_PIPE)
			fdin = nextfdin;
		token = token->next;
	}
	//print_open_fds();
	ct2 = -1;
	while (++ct2 < ct)
		waitpid(id[ct2], &status, 0);	
	free(id);
	
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