/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:27:07 by amejia            #+#    #+#             */
/*   Updated: 2023/04/29 13:08:32 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_envfind(char *name)
{
	t_env	*token;

	token = g_state.envp;
	while (token != NULL && name != NULL)
	{
		if (ft_strncmp(token->name, name, -1) == 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

//unset
void	ft_envunset(t_env *token)
{
	t_env	*result;
	t_env	*next;

	result = ft_envfind(token->name);
	if (result == NULL)
		return ;
	if (result == g_state.envp)
	{
		next = g_state.envp->next;
		ft_envdelone(result);
		g_state.envp = next;
	}
	else
		ft_envdelone(result);
}

//export
void	ft_envset(t_env *token)
{
	ft_envunset(token);
	ft_envadd_back(&g_state.envp, token);
}

//env
int	ft_envprint(void)
{
	t_env	*env;

	env = g_state.envp;
	while (env != NULL)
	{
		ft_printf("%s=%s\n", env->name, env->args);
		env = env->next;
	}
	return (0);
}
