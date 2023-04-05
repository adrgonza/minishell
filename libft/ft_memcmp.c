/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:54:29 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 23:33:48 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{	
	unsigned int	counter;

	counter = 0;
	while (((unsigned char *)s1)[counter] == ((unsigned char *)s2)[counter] \
		&& counter < n)
	{
		counter++;
		if (counter == n)
			break ;
	}
	if (counter == n)
		return (0);
	else
		return (((unsigned char *)s1)[counter] - \
		((unsigned char *)s2)[counter]);
}
