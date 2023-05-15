/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:54:03 by amejia            #+#    #+#             */
/*   Updated: 2023/05/15 00:01:44 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtinexec(t_token *token)
{
	int		status;
	char	*lower;

	lower = ft_strtolower(token->args[0]);
	if (ft_strncmp(lower, "cd", -1) == 0)
		status = builtin_cd(token);
	if (ft_strncmp(lower, "export", -1) == 0)
		status = builtin_export(token);
	if (ft_strncmp(lower, "unset", -1) == 0)
		status = builtin_unset(token);
	if (ft_strncmp(lower, "env", -1) == 0)
		status = builtin_env(token);
	if (ft_strncmp(lower, "pwd", -1) == 0)
		status = builtin_pwd(token);
	if (ft_strncmp(lower, "exit", -1) == 0)
		status = builtin_exit(token);
	if (ft_strncmp(lower, "echo", -1) == 0)
		status = builtin_echo(token);
	free (lower);
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
	else if (ft_strncmp(token->args[1],"--",-1) == 0)
		;
	else if (ft_strncmp(token->args[1],"-",-1) == 0)
	{
		direnv = ft_envfind("OLDPWD");
		if (direnv == NULL)
		{
			write(STDERR_FILENO, "Minishell: cd: OLDPWD not set\n",31);
			return (1);
		}
		else 
			error = chdir(direnv->args);
		printf("%s\n",direnv->args);
	}
	else
		error = chdir(token->args[1]);
	if (error == -1)
		return (builtin_error());
	direnv = ft_envnew("OLDPWD", last_dir);
	if (direnv == NULL)
		return (builtin_error());
	ft_envset(direnv);
	getcwd(last_dir, PATH_MAX +1);
	direnv = ft_envnew("PWD", last_dir);
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
