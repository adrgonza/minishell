/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:54:56 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 13:58:45 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int		counter;
	void				*to_return;

	to_return = s;
	counter = 0;
	while (counter < n)
	{
		*((unsigned char *)s) = c;
		s++;
		counter++;
	}
	return (to_return);
}
