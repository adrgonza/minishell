/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:42:13 by amejia            #+#    #+#             */
/*   Updated: 2023/04/25 16:54:33 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**pipe_generator(int npipes)
{
	int	**to_return;
	int	ct;

	to_return = (int **)ft_calloc(npipes, sizeof(int *));
	if (to_return == 0)
		return (0);
	ct = 0;
	while (ct < npipes)
	{
		to_return[ct] = ft_calloc(2, sizeof(int));
		if (to_return[ct] == 0)
			break ;
		ct++;
	}
	if (ct == npipes)
	{
		while (ct-- > 0)
			pipe(to_return[ct]);
		return (to_return);
	}
	else
		while (ct-- > 0)
			free(to_return[ct]);
	return (free(to_return), (int **)0);
}

int	pipe_counter(t_token *token)
{
	int	c;

	c = 0;
	while (token != NULL)
	{
		if (token->type == T_LESS || token->type == T_LESSLESS || \
			token->type == T_GREAT || token->type == T_GREATGREAT || \
			token->type == T_COMMAND || token->type == T_STDIN || \
			token->type == T_STDOUT)
			c++;
		token = token->next;
	}
	return (ft_max(c - 1, 0));
}

void	pipe_con_before_forks(t_token *token, int **pip, int n_pipes)
{
	t_token	*end;

	end = token;
	while (end->next != NULL)
		end = end->next;
	if (token->type == T_LESS)
		pip[0][0] = open(token->args[0],O_RDONLY);
	else if (token->type == T_LESSLESS)
		here_doc_prompt(pip[0], token);
	else if (token->type == T_STDIN)
		pip[0][0] = dup(STDIN_FILENO);
	if (end->type == T_GREAT)
		pip[n_pipes - 1][1] = open(end->args[0], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (end->type == T_GREATGREAT)
		pip[n_pipes - 1][1] = open(end->args[0], \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (end->type == T_STDOUT)
	 	pip[n_pipes - 1][1] = dup(STDOUT_FILENO);
}

void	here_doc_prompt(int *pip, t_token *token)
{
	char	*command;

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
}
