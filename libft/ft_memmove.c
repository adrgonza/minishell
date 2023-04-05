/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:54:46 by amejia            #+#    #+#             */
/*   Updated: 2023/02/17 22:39:58 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	counter;

	if (len == 0 || (dst == 0 && src == 0))
		return (dst);
	if (dst < src)
	{
		counter = 0;
		while (counter < len)
		{
			*((char *)(dst + counter)) = *((char *)(src + counter));
			counter++;
		}
	}
	else
	{
		counter = len - 1;
		while (1)
		{
			*((char *)(dst + counter)) = *((char *)(src + counter));
			if (counter == 0)
				break ;
			counter--;
		}
	}
	return (dst);
}
