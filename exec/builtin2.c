/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:57 by amejia            #+#    #+#             */
/*   Updated: 2023/05/11 17:49:13 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_token *token)
{
	t_env	*env;
	char	**localsplit;
	int		ct;

	ct = 1;
	while (token->args[ct] != NULL)
	{
		localsplit = ft_split(token->args[ct], '=');
		if (localsplit == NULL || *localsplit == NULL)
			return (builtin_error());
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
		if (fd == -1)
			return (1);
		write(fd, cwd, strlen(cwd));
		write(fd, "\n", 1);
	}
	env = ft_envnew("PWD", cwd);
	if (env == NULL)
		return (builtin_error());
	ft_envset(env);
	return (0);
}

int	builtin_echosetfd(t_token *token, int *fd)
{
	if (g_state.am_child == 0)
	{
		*fd = set_pipeoutput(token, NULL);
		if (*fd == -1)
			return (1);
	}
	else
		*fd = STDOUT_FILENO;
	return (0);
}

int	builtin_echo(t_token *token)
{
	int	ct;
	int	mode;
	int	fd;

	mode = 0;
	ct = 1;
	if (builtin_echosetfd(token, &fd) == 1)
		return (1);
	if (token->args != NULL && ft_strncmp(token->args[0], "-n", -1) == 0)
	{
		ct++;
		mode = 1;
	}
	if (token->args != NULL)
	{
		while (token->args[ct] != NULL)
		{
			write(fd, token->args[ct], ft_strlen(token->args[ct]));
			if (token->args[++ct] != NULL)
				write(fd, " ", 1);
		}
	}
	if (mode == 0)
		write(fd, "\n", 1);
	return (0);
}

int	builtin_exit(t_token *token)
{
	while (token->last != NULL)
		token = token->last;
	ft_tknclear(&token);
	ft_envclear(&g_state.envp);
	exit (g_state.last_return);
	return (0);
}
