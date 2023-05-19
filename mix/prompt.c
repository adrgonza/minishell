/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/05/19 13:07:29 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt_chooser(void)
{
	static int	mode;

	if (g_state.last_return == 0)
	{
		mode++;
		if (mode % 5 == 1)
			return ("\033[0;35m(>^.^)> \033[0;37m");
		if (mode % 5 == 2)
			return ("\033[0;35m<(^.^<) \033[0;37m");
		if (mode % 5 == 3)
			return ("\033[0;35m<(^.^)> \033[0;37m");
		if (mode % 5 == 4)
			return ("\033[0;35m^(^.^)^ \033[0;37m");
		if (mode % 5 == 0)
			return ("\033[0;35mv(^.^)v \033[0;37m");
	}
	return ("\033[0;31m(>x.x)> \033[0;37m");
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
		tokens = parsing(command);
		free(command);
		if (tokens)
		{
			ft_executer(tokens);
			ft_tknclear(&tokens);
		}
	}
}
