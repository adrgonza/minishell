/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/04/24 16:31:10 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt(char **envp)
{
	char	*command;
	t_token	*tokens;
	t_token *last;
	command = (char *)1;
	while (command != NULL)
	{
		command = readline("(>^-^)> ");
		if (command == NULL)
			break ;
		add_history(command);
		tokens = parsing(command);
		if (tokens)
			ft_executer(tokens);
		ft_tknclear(&tokens);
		free(command);
	}
	//rl_clear_history();
}
