/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:12:35 by amejia            #+#    #+#             */
/*   Updated: 2023/04/24 21:30:03 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *prompt_chooser(void)
{
	if (g_state.last_return == 0)
		return("(>^.^)> ");
	return("(>-.-)> ");
}
void	prompt(void)
{
	char	*command;
	t_token	*tokens;
	t_token *last;
	char 	*prompt;
	
	command = (char *)1;
	while (command != NULL)
	{
		command = readline(prompt_chooser());
		if (command == NULL)
			break ;
		add_history(command);
		tokens = NULL;
		tokens = parsing(command);
		ft_executer(tokens);
		ft_tknclear(&tokens);
		free(command);
	}
	//rl_clear_history();
}

void	prompt_debug(void)
{
	t_token	*tokens;
	t_token *last;
	
	tokens = NULL;
	ft_tknadd_back(&tokens,ft_tknnew(T_STDIN, NULL));
	ft_tknadd_back(&tokens,ft_tknnew(T_COMMAND,ft_split("cat minishell.h", ' ')));
	ft_tknadd_back(&tokens,ft_tknnew(T_COMMAND,ft_split("grep int", ' ')));
	ft_tknadd_back(&tokens,ft_tknnew(T_COMMAND,ft_split("grep built", ' ')));
	ft_tknadd_back(&tokens,ft_tknnew(T_STDOUT, NULL));	
	ft_executer(tokens);
	ft_tknclear(&tokens);
}
