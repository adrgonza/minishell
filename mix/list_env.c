/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:25:18 by amejia            #+#    #+#             */
/*   Updated: 2023/04/23 22:31:26 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*mover;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	mover = *lst;
	while (mover->next != NULL)
		mover = mover -> next;
	mover->next = new;
	new->last = mover;
}

void	ft_envadd_front(t_env **lst, t_env *new)
{
	(*lst)->last = new;
	new->next = *lst;
	*lst = new;
}

void	ft_envclear(t_env **lst)
{
	if (*lst == 0)
		return ;
	if ((*lst)->next != 0)
		ft_envclear(&((*lst)->next));
	ft_envdelone(*lst);
	*lst = 0;
}

void	ft_envdelone(t_env *lst)
{
	if (lst == 0)
		return ;
	if (lst->name != NULL)
		free (lst->name);
	if (lst->args != NULL)
		free (lst->args);
	if (lst->next != NULL)
		lst->next->last = lst->last;
	if (lst->last != NULL)
		lst->last->next = lst->next;
	free(lst);
}

t_env	*ft_envlast(t_env *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
		lst = lst-> next;
	return (lst);
}
