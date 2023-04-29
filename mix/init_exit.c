/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:10:16 by amejia            #+#    #+#             */
/*   Updated: 2023/04/29 13:23:29 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_init(int argc, char **argv, char **envp)
{
	t_env *envt;
	if (argc != 1) /* check there is only an argument */
		return (0);
	g_state.envp = env_split_to_list(envp); /* copy the external env */
	g_state.am_child = 0;
	envt = ft_envnew("SHELL",argv[0]);
	if (envt == NULL)
	{
		ft_printf("Memory problem");
		exit (EXIT_FAILURE);
	}
	ft_envset(envt);
	return (1);
}

void ft_exit(void)
{
	ft_envclear(&g_state.envp);
	exit(0);
}
//Function to deal with failed mallocs. To be filled.
void malloc_fail_proc(void)
{
	ft_envclear(&g_state.envp);
	perror("Memory Problems") ;
	exit(EXIT_FAILURE) ;
}
