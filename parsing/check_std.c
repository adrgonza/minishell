/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:36:09 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/10 16:29:55 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_stdin(t_token *token)
{
	while (token)
	{
		if (token->type == T_PIPE)
			return (1);
		if (token->type == T_LESS || token->type == T_LESSLESS)
			return (0);
		token = token->next;
	}
	return (1);
}

int	check_stdout(t_token *token)
{
	while (token->next)
		token = token->next;
	if (token->type == T_GREAT || token->type == T_GREATGREAT)
		return (0);
	return (1);
}
