/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:10:16 by amejia            #+#    #+#             */
/*   Updated: 2023/05/13 22:04:28 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_init(int argc, char **argv, char **envp)
{
	t_env	*envt;
	char	cwd[PATH_MAX + 1];

	if (argc != 1) /* check there is only an argument */
		return (0);
	g_state.envp = env_split_to_list(envp); /* copy the external env */
	g_state.am_child = 0;
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
	g_state.last_dir = ft_strdup(cwd);
	if (g_state.last_dir == NULL)
		malloc_fail_proc();	
	envt = ft_envnew("SHELL", argv[0]);
	if (envt == NULL)
		malloc_fail_proc();
	ft_envset(envt);
	return (1);
}

void	ft_exit(t_token *token)
{
	int a;
	
	if (token->args != NULL && token->args[1] != NULL)
		a = ft_atoi(token->args[1]);
	else
		a = 0;
	ft_envclear(&g_state.envp);
	free(g_state.home_dir);
	free(g_state.last_dir);
	exit(a);
}

//Function to deal with failed mallocs. To be filled.
void	malloc_fail_proc(void)
{
	ft_envclear(&g_state.envp);
	free(g_state.home_dir);
	free(g_state.last_dir);
	perror("Memory Problems") ;
	exit(EXIT_FAILURE) ;
}
