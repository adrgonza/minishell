/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:37:32 by amejia            #+#    #+#             */
/*   Updated: 2023/05/20 20:02:24 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc_loop(char *command, t_token *token, int *pip)
{
	while (1)
	{
		command = readline("heredoc(>^.^)> ");
		if (command == NULL)
			break ;
		if (ft_strncmp(command, token->args[0], -1) == 0)
			break ;
		else
		{
			if (g_state.here_quote == 0)
			{
				g_state.here_quote = 1;
				command = check_quotes(command);
			}
			if (command == NULL)
				return (close(pip[1]), close(pip[0]), -1);
			write(pip[1], command, ft_strlen(command));
			write(pip[1], "\n", 1);
		}
		free(command);
		command = NULL;
	}
	free(command);
	return (0);
}

int	here_doc_prompt(t_token *token)
{
	int		pip[2];
	char	*command;

	g_state.status = S_HEREDOC;
	command = NULL;
	if (token->args[0] == NULL)
	{
		write(STDERR_FILENO, \
			"syntax error near unexpected token `newline\n", 44);
		g_state.last_return = 2;
		return (-1);
	}
	pipe(pip);
	if (here_doc_loop(command, token, pip) == -1)
		return (-1);
	close(pip[1]);
	return (pip[0]);
}
