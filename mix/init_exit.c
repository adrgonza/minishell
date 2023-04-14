/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:10:16 by amejia            #+#    #+#             */
/*   Updated: 2023/04/06 23:13:46 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_init(int argc, char **argv, char **envp)
{
	if (argc != 1) /* check there is only an argument */
		return (0);
	split_cpy(&g_state.envp,envp); /* copy the external env */
	return (1);
}

void ft_exit(void)
{
	ft_free_split(g_state.envp);
	exit(0);
}