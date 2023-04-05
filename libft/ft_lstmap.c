/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:51:49 by amejia            #+#    #+#             */
/*   Updated: 2023/01/28 20:59:07 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*holding;
	t_list	*start;
	t_list	*to_return;

	to_return = 0;
	start = lst;
	if (lst == 0)
		return (0);
	while (1)
	{
		holding = ft_lstnew((*f)(lst->content));
		if (holding == 0)
		{
			ft_lstclear(&start, del);
			return (0);
		}
		else if (to_return == 0)
			to_return = holding;
		else
			ft_lstadd_back(&to_return, holding);
		if (lst -> next == 0)
			break ;
		lst = lst->next;
	}
	return (to_return);
}
