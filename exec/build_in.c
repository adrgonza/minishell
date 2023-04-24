/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:54:03 by amejia            #+#    #+#             */
/*   Updated: 2023/04/23 22:44:40 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_builtinexec(t_token *token)
{
	if (ft_strncmp(token->args[0],"cd",-1) == 0)
		builtin_cd(token);
	if (ft_strncmp(token->args[0],"export",-1) == 0)
		builtin_export(token);
	if (ft_strncmp(token->args[0],"unset",-1) == 0)
		builtin_unset(token);
	if (ft_strncmp(token->args[0],"env",-1) == 0)
		ft_envprint();
	if (ft_strncmp(token->args[0],"pwd",-1) == 0)
		builtin_pwd();
	
}

int	builtin_cd(t_token *token)
{
	int		error;
	t_env	*direnv;

	error = chdir(token->args[0]);
	if (error = -1)
	{
		ft_printf("could not change dirs");
		g_state.last_return = 1;
		return (1);
	}
	direnv = ft_envnew("PWD",token->args[0]);
	if (direnv == NULL)
	{
		g_state.last_return = -1;
		exit(EXIT_FAILURE);
	}
	ft_envset(direnv);
	return (0);
}

int	builtin_export(t_token *token)
{
	int		error;
	t_env	*env;
	char	**localsplit;
	int		ct;

	ct = 1;
	while (token->args[ct] != NULL)
	{
		localsplit = ft_split(token->args[ct], "=");
		env = ft_envnew(localsplit[0],localsplit[1]);
		if (env == NULL)
			exit(EXIT_FAILURE);
		ft_envset(token);
		ft_free_split(localsplit);
		ct++;
	}
	return (0);
}

int	builtin_unset(t_token *token)
{
	t_env	*env;
	char	**localsplit;
	int		ct;

	ct = 1;
	while (token->args[ct] != NULL)
	{
		localsplit = ft_split(token->args[ct], "=");
		env = ft_envnew(localsplit[0],localsplit[1]);
		if (env == NULL)
			exit(EXIT_FAILURE);
		ft_envunset(token);
		ft_free_split(localsplit);
		ft_envdelone(env);
		ct++;
	}
	return (0);
}

int	builtin_pwd()
{
	t_env	*env;
	char	cwd[PATH_MAX + 1];

	ft_bzero(cwd, PATH_MAX +1);
	getcwd(cwd, PATH_MAX);
	env = ft_envnew("PWD",cwd);
	if (env == NULL)
	{
		exit(EXIT_FAILURE);
	}
	ft_envset(env);
	return (0);
}
