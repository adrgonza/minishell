/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:08:57 by amejia            #+#    #+#             */
/*   Updated: 2023/05/25 17:00:27 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_token *token)
{
	char	*lower;
	int		ret_val;

	ret_val = 1;
	lower = token->args[0];
	if (!ft_strncmp(lower, "cd", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "export", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "unset", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "env", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "pwd", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "exit", -1))
		ret_val = 0;
	if (!ft_strncmp(lower, "echo", -1))
		ret_val = 0;
	return (ret_val);
}

int	builtin_env(t_token *token)
{
	if (token->args[1] != NULL)
	{
		g_state.last_return = 127;
		return (builtin_error());
	}
	else
		return (ft_envprint());
}

int	builtin_unset(t_token *token)
{
	t_env	*env;
	char	**localsplit;
	int		ct;

	ct = 0;
	while (token->args[++ct] != NULL)
	{
		localsplit = ft_split(token->args[ct], '=');
		if (localsplit == NULL)
			return (builtin_error());
		if (*localsplit == NULL)
		{
			ft_free_split(localsplit);
			return (builtin_error());
		}
		if (checkarg_export2(localsplit[0]) == -1)
			return (ft_free_split(localsplit), not_vallid_id(localsplit[0]));
		env = ft_envnew(localsplit[0], localsplit[1]);
		if (env == NULL)
			return (builtin_error());
		ft_envunset(env);
		ft_free_split(localsplit);
		ft_envdelone(env);
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

void	export_if(t_token *token, char **str, int ct)
{
	str[2] = ft_strchr(token->args[ct], '=');
	if (str[2] != 0)
	{
		str[0] = ft_substr(token->args[ct], 0,
				(unsigned int)(str[2] - token->args[ct]));
		str[1] = ft_substr(str[2] + 1, 0, ft_strlen(str[2] + 1));
	}
	else
	{
		str[0] = ft_substr(token->args[ct], 0, ft_strlen(token->args[ct]));
		str[1] = ft_strdup("");
	}
}
