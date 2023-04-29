/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/04/29 23:37:35 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt_chooser(void)
{
	if (g_state.last_return == 0)
		return ("(>^.^)> ");
	return ("(>x.x)> ");
}

void	prompt(void)
{
	char	*command;
	t_token	*tokens;
	t_token	*last;
	char	*prompt;

	command = (char *)1;
	while (command != NULL)
	{
		command = readline(prompt_chooser());
		if (command == NULL)
			break ;
		add_history(command);
		tokens = parsing(command);
		if (tokens)
		{
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
		free(command);
	}
}

void	prompt_debug(void)
{
	char	*command;
	t_token	*tokens;
	t_token	*last;
	char	*prompt;

	command = (char *)1;
	while (command != NULL)
	{
		command = ft_strdup("cot");
		if (command == NULL)
			break ;
		tokens = parsing(command);
		if (tokens)
		{
			ft_print_tkns(tokens);
			tokens = redirect_order_sort(tokens);
			ft_print_tkns(tokens);
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
		free(command);
		command = NULL;
	}
}
