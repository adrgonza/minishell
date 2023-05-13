/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:57 by amejia            #+#    #+#             */
/*   Updated: 2023/05/13 21:34:47 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_token *token)
{
	int		status;
	char	*lower;
	int		ret_val;

	ret_val = 1;
	lower = token->args[0];
	if (!ft_strncmp(lower, "cd", -1) || !ft_strncmp(lower, "CD", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "export", -1) || !ft_strncmp(lower, "EXPORT", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "unset", -1) || !ft_strncmp(lower, "UNSET", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "env", -1) || !ft_strncmp(lower, "ENV", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "pwd", -1) || !ft_strncmp(lower, "PWD", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "exit", -1) || !ft_strncmp(lower, "EXIT", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "echo", -1) || !ft_strncmp(lower, "ECHO", -1))
		ret_val = 0;
	return (ret_val);
}
