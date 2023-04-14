/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/04/06 18:12:38 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt(char **envp)
{
	char	*command;
	t_token	*tokens;

	command = (char *)1;
	while (command != NULL)
	{
		command = readline("(>\'-\')> ");
		if (command == NULL)
			break ;
		add_history(command);
		tokens = ft_parsing(command);
		ft_executer(tokens);
		ft_tknclear(&tokens);
		free(command);
	}
}
