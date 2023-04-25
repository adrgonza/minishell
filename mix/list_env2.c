/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:01 by amejia            #+#    #+#             */
/*   Updated: 2023/04/25 16:34:03 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_envnew(char *name, char *args)
{
	t_env	*to_return;

	to_return = (t_env *)malloc(sizeof(t_env));
	if (to_return == 0)
		return (0);
	to_return->name = ft_strdup(name);
	if (to_return->name == NULL)
	{
		free (to_return);
		return (NULL);
	}
	if (args != NULL)
		to_return->args = ft_strdup(args);
	else
		to_return->args = NULL;
	if (args != NULL && to_return->args == NULL)
	{
		free(to_return->name);
		free(to_return);
		return (NULL);
	}
	to_return->next = NULL;
	to_return->last = NULL;
	return (to_return);
}

int	ft_envsize(t_env *lst)
{
	int	counter;

	if (lst == NULL)
		return (0);
	counter = 1;
	while (lst->next != NULL)
	{
		if (lst->next != NULL)
			lst = lst-> next;
		counter++;
	}
	return (counter);
}

t_env	*env_split_to_list(char **env)
{
	t_env	*to_return;
	t_env	*middle;
	char	**str;
	int		ct;

	ct = 0;
	to_return = NULL;
	while (env[ct] != NULL)
	{
		str = ft_split(env[ct], '=');
		if (str == NULL)
		{
			ft_envclear(&to_return);
			return (NULL);
		}
		middle = ft_envnew(str[0], str[1]);
		free(str);
		if (middle == NULL)
			return (ft_envclear(&to_return), NULL);
		ft_envadd_back(&to_return, middle);
		ct++;
	}
	return (to_return);
}

char	**env_list_to_split(t_env *token)
{
	int		env_len;
	char	**to_return;
	char	*temp;

	env_len = ft_envsize(token);
	to_return = ft_calloc(env_len + 1, sizeof(char *));
	if (to_return == 0)
		return (0);
	env_len = 0;
	while (token != NULL)
	{
		temp = ft_strjoin(token->name, "=");
		if (temp == NULL)
			return (ft_free_split(to_return), NULL);
		if (token->args != NULL)
			to_return[env_len] = ft_strjoin(temp, token->args);
		else
			to_return[env_len] = ft_strdup(temp);
		free (temp);
		if (to_return[env_len] == NULL)
			return (ft_free_split(to_return), NULL);
		env_len++;
		token = token->next;
	}
	return (to_return);
}
