/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:57 by amejia            #+#    #+#             */
/*   Updated: 2023/05/13 16:54:54 by amejia           ###   ########.fr       */
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
	if (ft_strncmp(lower, "cd", -1) == 0)
		ret_val = 0;
	if (ft_strncmp(lower, "export", -1) == 0)
		ret_val = 0;
	if (ft_strncmp(lower, "unset", -1) == 0)
		ret_val = 0;
	if (ft_strncmp(lower, "env", -1) == 0)
		ret_val = 0;
	if (ft_strncmp(lower, "pwd", -1) == 0)
		ret_val = 0;
	if (ft_strncmp(lower, "exit", -1) == 0)
		ret_val = 0;
	if (ft_strncmp(lower, "echo", -1) == 0)
		ret_val = 0;
	free (lower);
	return (ret_val);
}
