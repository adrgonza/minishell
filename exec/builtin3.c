/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:57 by amejia            #+#    #+#             */
/*   Updated: 2023/05/15 00:00:32 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_token *token)
{
	int		status;
	char	*lower;
	int		ret_val;

	ret_val = 1;
	lower = ft_strtolower(token->args[0]);
	if (!ft_strncmp(lower, "cd", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "export", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "unset", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "env", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "pwd", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "exit", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "echo", -1))
		ret_val = 0;
	return (ret_val);
}

int	builtin_env(t_token *token)
{
	if(token->args[1] != NULL)
	{
		g_state.last_return = 127;
		return (builtin_error());
	}
	else
		return(ft_envprint());
}