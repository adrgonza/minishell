/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exectkn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:13:06 by amejia            #+#    #+#             */
/*   Updated: 2023/05/02 17:39:58 by adrgonza         ###   ########.fr       */
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

//this function mallocs its result
char	*find_path(char *command, char **envp)
{
	char	*path;
	char	**temp;
	char	**envpaths;
	int		c;

	if (command == 0)
		return (0);
	if (!access(command, X_OK))
		return (command);
	path = ft_strjoin("./", command);
	if (path != 0 && !access(path, X_OK))
		return (free(command), path);
	else if (path == 0)
		return (free(command), NULL);
	free(path);
	c = -1;
	while (envp[++c] != NULL && !ft_strnstr(envp[c], "PATH", 4))
		;
	if (envp[c] == NULL)
		exit (EXIT_FAILURE);
	temp = ft_split(envp[c], '=');
	envpaths = ft_split(temp[1], ':');
	ft_free_split(temp);
	return (find_path2(command, envpaths));
}

int	ft_exectkn(t_token *token)
{
	char	*path_to_exec;

	path_to_exec = find_path((token->args)[0], env_list_to_split(g_state.envp));
	if (path_to_exec == NULL)
	{
		perror("Minishell: Command not found");
		exit(127);
	}
	if (execve(path_to_exec, token->args,
			env_list_to_split(g_state.envp)) == -1)
	{
		perror("execve");
		exit (126);
	}
	return (0);
}
