/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exectkn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:13:06 by amejia            #+#    #+#             */
/*   Updated: 2023/05/16 12:21:50 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path2(char *command, char **envpaths)
{
	int		ct;
	char	*path;
	char	*temp;

	ct = 0;
	while (envpaths[ct] != NULL)
	{
		path = ft_strjoin(envpaths[ct], "/");
		if (path == 0)
			exit (EXIT_FAILURE);
		temp = path;
		path = ft_strjoin(path, command);
		if (path == 0)
			exit (EXIT_FAILURE);
		free(temp);
		if (!access(path, F_OK))
			return (free(command), ft_free_split(envpaths), path);
		ct++;
	}
	free(command);
	ft_free_split(envpaths);
	return (NULL);
}

void	find_path3(char **envp, char *command, char ***envpaths)
{
	int		c;
	char	**temp;

	c = -1;
	while (envp[++c] != NULL && !ft_strnstr(envp[c], "PATH", 4))
		;
	if (envp[c] == NULL || ft_strlen(envp[c]) <= 5)
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDOUT_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": Command not found\n", 20);
		exit (127);
	}
	temp = ft_split(envp[c], '=');
	*envpaths = ft_split(temp[1], ':');
	ft_free_split(temp);
}

//this function mallocs its result
char	*find_path(char *command, char **envp)
{
	char	*path;
	char	**envpaths;

	if (command == 0)
		return (0);
	if (!access(command, X_OK))
		return (command);
	if (ft_strchr(command, '/') > 0)
		return (NULL);
	path = ft_strjoin("./", command);
	if (path != 0 && !access(path, X_OK))
		return (free(command), path);
	else if (path == 0)
		return (free(command), NULL);
	free(path);
	envpaths = NULL;
	find_path3(envp, command, &envpaths);
	return (find_path2(command, envpaths));
}

int	ft_exectkn(t_token *token)
{
	char	*path_to_exec;
	char	**env;

	env = env_list_to_split(g_state.envp);
	path_to_exec = find_path((token->args)[0], env);
	if (path_to_exec == NULL)
	{
		perror("Minishell: Command not found");
		ft_free_split(env);
		exit(127);
	}
	if (execve(path_to_exec, token->args,
			env) == -1)
	{
		perror("execve");
		ft_free_split(env);
		exit (127);
	}
	return (0);
}
