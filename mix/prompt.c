/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/05/11 17:40:32 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt_chooser(void)
{
	if (g_state.last_return == 0)
		return ("\033[0;35m(>^.^)> \033[0;37m");
	return ("\033[0;31m(>x.x)> \033[0;37m");
}

void	prompt(void)
{
	char	*command;
	t_token	*tokens;
	t_token	*last;
	char	*prompt;

	//signal(SIGINT, sig_hnd);
	//signal(SIGQUIT, sig_hnd);
	command = (char *)1;
	while (command != NULL)
	{
		//ft_printf("%d\n",g_state.last_return);
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
	int		w;

	w = 0;
	command = (char *)1;
	while (command != NULL)
	{
		if (w % 2 == 0)
			command = ft_strdup("/");
		else
			command = ft_strdup("echo $?");
		if (command == NULL)
			break ;
		tokens = parsing(command);
		if (tokens)
		{
			ft_print_tkns(tokens);
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
		free(command);
		//command = NULL;
		w++;
	}
}
