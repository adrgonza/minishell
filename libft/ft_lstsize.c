/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:57:50 by amejia            #+#    #+#             */
/*   Updated: 2023/01/28 20:58:28 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
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
