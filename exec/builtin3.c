/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:57 by amejia            #+#    #+#             */
/*   Updated: 2023/04/29 22:54:29 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_token *token)
{
	if (ft_strncmp(token->args[0], "cd", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "export", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "unset", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "env", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "pwd", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "exit", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "echo", -1) == 0)
		return (0);
	return (1);
}
