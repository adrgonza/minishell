/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:10:16 by amejia            #+#    #+#             */
/*   Updated: 2023/05/23 18:49:12 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	global_init(void)
{
	g_state.here_quote = 0;
	g_state.am_child = 0;
	g_state.expand = 0;
	g_state.id = NULL;
	g_state.status = 0;
}

int	ft_init(int argc, char **argv, char **envp)
{
	t_env	*envt;
	char	cwd[PATH_MAX + 1];

	if (argc != 1)
		return (0);
	signal(SIGINT, sig_hnd);
	signal(SIGQUIT, SIG_IGN);
	global_init();
	g_state.envp = env_split_to_list(envp);
	envt = ft_envfind("HOME");
	if (envt != NULL && envt->args != NULL)
	{
		g_state.home_dir = ft_strdup(envt->args);
		if (g_state.home_dir == NULL)
			malloc_fail_proc();
	}
	else
		g_state.home_dir = NULL;
	getcwd(cwd, PATH_MAX + 1);
	envt = ft_envnew("SHELL", argv[0]);
	if (envt == NULL)
		malloc_fail_proc();
	ft_envset(envt);
	return (1);
}

//Function to deal with failed mallocs. To be filled.
void	malloc_fail_proc(void)
{
	ft_envclear(&g_state.envp);
	free(g_state.home_dir);
	perror("Memory Problems");
	exit(EXIT_FAILURE);
}
