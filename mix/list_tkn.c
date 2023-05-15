/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tkn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:25:18 by amejia            #+#    #+#             */
/*   Updated: 2023/05/15 23:05:10 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tknadd_back(t_token **lst, t_token *new)
{
	t_token	*mover;

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

void	ft_tknadd_front(t_token **lst, t_token *new)
{
	(*lst)->last = new;
	new->next = *lst;
	*lst = new;
}

void	ft_tknclear(t_token **lst)
{
	if (*lst == 0)
		return ;
	if ((*lst)->next != 0)
		ft_tknclear(&((*lst)->next));
	ft_tkndelone(*lst);
	*lst = 0;
}

void	ft_tkndelone(t_token *lst)
{
	if (lst == 0)
		return ;
	if (lst->args != NULL)
		;//ft_free_split(lst->args);
	free(lst);
}

t_token	*ft_tknlast(t_token *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
		lst = lst-> next;
	return (lst);
}
