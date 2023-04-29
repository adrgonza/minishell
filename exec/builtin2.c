/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:57 by amejia            #+#    #+#             */
/*   Updated: 2023/04/29 13:32:22 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_token *token)
{
	if (ft_strncmp(token->args[0], "cd", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "export", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "unset", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "env", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "pwd", -1) == 0)
		return (0);
	if (ft_strncmp(token->args[0], "exit", -1) == 0)
		return (0);
	return (1);
}

int	builtin_unset(t_token *token)
{
	t_env	*env;
	char	**localsplit;
	int		ct;

	ct = 1;
	while (token->args[ct] != NULL)
	{
		localsplit = ft_split(token->args[ct], '=');
		env = ft_envnew(localsplit[0], localsplit[1]);
		if (env == NULL)
			return (builtin_error());
		ft_envunset(env);
		ft_free_split(localsplit);
		ft_envdelone(env);
		ct++;
	}
	return (0);
}

int	builtin_pwd(t_token *token)
{
	t_env	*env;
	char	cwd[PATH_MAX + 1];
	int		fd;

	ft_bzero(cwd, PATH_MAX +1);
	getcwd(cwd, PATH_MAX);
	if (g_state.am_child == 1)
		ft_printf("%s\n", cwd);
	else
	{
		fd = set_pipeoutput(token, NULL);
		write(fd, cwd, strlen(cwd));
		write(fd, "\n", 1);
		close(fd);
	}
	env = ft_envnew("PWD", cwd);
	if (env == NULL)
		return (builtin_error());
	ft_envset(env);
	return (0);
}

int	builtin_echo(t_token *token)
{
	if (token->args[1] == 0)
		ft_printf("\n");
	else
		ft_printf("%s\n", token->args[1]);
	return (0);
}

int	builtin_exit(t_token *token)
{
	while (token->last != NULL)
		token = token->last;
	ft_tknclear(&token);
	ft_envclear(&g_state.envp);
	exit (0);
	return (0);
}
