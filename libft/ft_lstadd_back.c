/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:46:37 by amejia            #+#    #+#             */
/*   Updated: 2023/01/28 20:48:03 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*mover;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	mover = *lst;
	while (mover->next != NULL)
		mover = mover -> next;
	mover->next = new;
}
