/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:57:15 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 14:12:16 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	counter;

	counter = 0;
	while (counter < n)
	{
		if (*(s1 + counter) != *(s2 + counter) || *(s1 + counter) == '\0' || \
		*(s2 + counter) == '\0')
			return (*((unsigned char *)(s1 + counter)) - \
			*((unsigned char *)(s2 + counter)));
		counter++;
	}
	return (0);
}
