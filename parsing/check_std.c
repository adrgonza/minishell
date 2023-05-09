/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_std.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:36:09 by adrgonza          #+#    #+#             */
/*   Updated: 2023/05/08 15:27:49 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_stdin(t_token *token)
{
	while (token)
	{
		if (token->type == T_LESS)
			return (0);
		token = token->next;
	}
	return (1);
}

int	check_stdout(t_token *token)
{
	while (token)
	{
		if (token->type == T_GREAT)
			return (0);
		token = token->next;
	}
	return (1);
}
