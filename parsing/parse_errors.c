/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:11:34 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/23 18:20:54 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes_cmd(t_token *token)
{
	int	cmd_pipe[2];

	cmd_pipe[1] = 1;
	cmd_pipe[0] = 0;
	while (token)
	{
		if (token->type == T_COMMAND || (token->type <= 9 && token->type >= 6))
		{
			cmd_pipe[0] = 1;
			cmd_pipe[1] = 1;
		}
		if (token->type == T_PIPE)
		{
			if (cmd_pipe[0] == 0)
				return (ft_putstr_fd(
						"syntax error near unexpected token `|'\n", 2), 0);
			cmd_pipe[0] = 0;
			cmd_pipe[1] = 0;
		}
		token = token->next;
	}
	if (cmd_pipe[1] == 0)
		return (ft_putstr_fd(
				"syntax error near unexpected token `|'\n", 2), 0);
	return (1);
}

int	check_parsing_errors(char cmd, int s_qte, int d_qte)
{
	if (cmd == ';' && s_qte % 2 == 0 && d_qte % 2 == 0)
		return (ft_putstr_fd("Syntax error near unexpected token `;'\n", 2),
			g_state.last_return = 1, 0);
	if (cmd == '\\' && s_qte % 2 == 0 && d_qte % 2 == 0)
		return (ft_putstr_fd("Syntax error near unexpected token `\\'\n", 2),
			g_state.last_return = 1, 0);
	return (1);
}

int	check_redict_arg(t_token *token)
{
	while (token)
	{
		if (token->type <= 9 && token->type >= 6 && !token->args[0])
			return (ft_putstr_fd(
					"Syntax error near unexpected token `newline'\n", 2), 0);
		token = token->next;
	}
	return (1);
}
