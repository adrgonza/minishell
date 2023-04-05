/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:54:37 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 13:54:12 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void			*to_return;
	unsigned int	counter;

	if (dest == 0 && src == 0)
	{
		return (0);
	}
		to_return = dest;
	counter = 0;
	while (counter < n)
	{
		*((char *)(dest + counter)) = *((char *)(src + counter));
		counter++;
	}
	return (to_return);
}
