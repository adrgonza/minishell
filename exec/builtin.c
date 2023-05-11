/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:54:03 by amejia            #+#    #+#             */
/*   Updated: 2023/05/11 23:45:00 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtinexec(t_token *token)
{
	int	status;

	if (ft_strncmp(token->args[0], "cd", -1) == 0)
		status = builtin_cd(token);
	if (ft_strncmp(token->args[0], "export", -1) == 0)
		status = builtin_export(token);
	if (ft_strncmp(token->args[0], "unset", -1) == 0)
		status = builtin_unset(token);
	if (ft_strncmp(token->args[0], "env", -1) == 0)
		status = ft_envprint();
	if (ft_strncmp(token->args[0], "pwd", -1) == 0)
		status = builtin_pwd(token);
	if (ft_strncmp(token->args[0], "exit", -1) == 0)
		status = builtin_exit(token);
	if (ft_strncmp(token->args[0], "echo", -1) == 0)
		status = builtin_echo(token);
	g_state.last_return = status;
}

int	builtin_error(void)
{
	perror("Minishell");
	g_state.last_return = 1;
	return (1);
}

int	builtin_cd(t_token *token)
{
	int		error;
	t_env	*direnv;
	char	last_dir[PATH_MAX+1];

	ft_bzero(last_dir,PATH_MAX + 1);
	getcwd(last_dir, PATH_MAX +1);
	if (token->args[1] == NULL)
	{
		direnv = ft_envfind("HOME");
		if (direnv == NULL)
			error = -1;
		else
			error = chdir(direnv->args);
	}
	else if (ft_strncmp(token->args[1],"-",-1) == 0)
	{
		error = chdir(g_state.last_dir);
		printf("%s\n",g_state.last_dir);
	}
	else
		error = chdir(token->args[1]);
	if (error == -1)
		return (builtin_error());
	free(g_state.last_dir);
	g_state.last_dir = ft_strdup(last_dir);
	direnv = ft_envnew("PWD", token->args[0]);
	if (direnv == NULL)
		return (builtin_error());
	ft_envset(direnv);
	
	return (0);
}


int	builtin_export_nargs(void)
{
	t_env	*env;

	env = g_state.envp;
	while (env != NULL)
	{
		ft_printf("declare -x %s=%s\n", env->name, env->args);
		env = env->next;
	}
	return (0);
}


int	builtin_export(t_token *token)
{
	int		error;
	t_env	*env;
	char	**localsplit;
	int		ct;

	ct = 1;
	if (token->args[ct] == NULL)
		return (builtin_export_nargs());
	while (token->args[ct] != NULL)
	{
		localsplit = ft_split(token->args[ct], '=');
		if (localsplit == NULL || *localsplit == NULL)
			return (builtin_error());
		env = ft_envnew(localsplit[0], localsplit[1]);
		if (env == NULL)
			return (builtin_error());
		ft_envset(env);
		ft_free_split(localsplit);
		ct++;
	}
	return (0);
}
