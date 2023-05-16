/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:54:03 by amejia            #+#    #+#             */
/*   Updated: 2023/05/16 22:36:07 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//arreglar /bin/echo 42 > /dev/null > /dev/null > /dev/null > /dev/null > tmp_redir_out

void	ft_builtinexec(t_token *token)
{
	int		status;
	char	*lower;

	lower = token->args[0];
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
		status = builtin_exit(token, id);
	if (ft_strncmp(lower, "echo", -1) == 0)
		status = builtin_echo(token);
	g_state.last_return = status;
}

int	builtin_error(void)
{
	perror("Minishell");
	g_state.last_return = 1;
	return (1);
}

int	builtin_cd_errorset(t_token *token, t_env **direnv)
{
	if (token->args[1] == NULL)
	{
		*direnv = ft_envfind("HOME");
		if (*direnv == NULL)
			return (-1);
		else
			return (chdir((*direnv)->args));
	}
	else if (ft_strncmp(token->args[1], "--", -1) == 0)
		return (0);
	else if (ft_strncmp(token->args[1], "-", -1) == 0)
	{
		*direnv = ft_envfind("OLDPWD");
		if (*direnv == NULL)
		{
			write(STDERR_FILENO, "Minishell: cd: OLDPWD not set\n", 31);
			return (2);
		}
		else
		{
			ft_printf("%s\n", (*direnv)->args);
			return (chdir((*direnv)->args));
		}
	}
	else
		return (chdir(token->args[1]));
}

int	builtin_cd(t_token *token)
{
	int		error;
	t_env	*direnv;
	char	last_dir[PATH_MAX + 1];

	ft_bzero(last_dir, PATH_MAX + 1);
	getcwd(last_dir, PATH_MAX +1);
	error = builtin_cd_errorset(token, &direnv);
	if (error == -1)
		return (builtin_error());
	if (error == 2)
		return (1);
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
