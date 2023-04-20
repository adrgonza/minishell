/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:27:07 by amejia            #+#    #+#             */
/*   Updated: 2023/04/20 22:46:20 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *ft_envfind(t_env *token, char *name)
{
	while(token != NULL && name != NULL)
	{
		if (ft_strncmp(token->name, name, -1) == 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

void ft_unsetkn(t_token *token)
{
	t_env	*result;

	result = ft_envfind(g_state->env,token->args[1]);
	if (result == NULL)
		return ;
	ft_envdelone(result);
}

void ft_settoken(t_token *token)
{
	t_env	*added;

	added = ft_envnew(token->args[0],token->args[1]);
	if (added == NULL)
	{
		ft_printf("Memory Error");
		return ;
	}
	ft_envadd_back(g_state->env,added);
}