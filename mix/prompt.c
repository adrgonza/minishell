/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/04/19 16:53:52 by amejia           ###   ########.fr       */
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
		//command = readline("(>^-^)> ");
		command = ft_strdup("ls -l");
		if (command == NULL)
			break ;
		add_history(command);
		tokens = NULL;
		ft_tknadd_back(&tokens,ft_tknnew(T_STDIN, ft_split("testmain.c", ' ')));
		ft_tknadd_back(&tokens,ft_tknnew(T_COMMAND,ft_split("ls", ' ')));
		//ft_tknadd_back(&tokens,ft_tknnew(T_COMMAND,ft_split("ls", ' ')));
		ft_tknadd_back(&tokens,ft_tknnew(T_GREAT, ft_split("out", ' ')));
		//tokens = parsing(command);
		if (tokens)
			ft_executer(tokens);
		ft_tknclear(&tokens);
		free(command);
		command = NULL;
	}
	//rl_clear_history();
}
