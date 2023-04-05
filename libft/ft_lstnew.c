/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:19:30 by amejia            #+#    #+#             */
/*   Updated: 2023/01/28 20:57:37 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*to_return;

	to_return = (t_list *)malloc(sizeof(t_list));
	if (to_return == 0)
		return (0);
	to_return->content = content;
	to_return->next = 0;
	return (to_return);
}
