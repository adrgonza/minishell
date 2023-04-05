/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:54:21 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 13:45:59 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	counter;

	counter = 0;
	while (counter < n)
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((void *)s);
		counter++;
		s++;
	}
	return (0);
}
