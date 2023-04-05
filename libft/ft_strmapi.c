/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:57:04 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 14:10:37 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		length_s;
	int		counter;
	char	*to_return;

	length_s = ft_strlen((char *)s);
	to_return = (char *)malloc(length_s + 1);
	if (to_return == 0)
		return (0);
	counter = 0;
	while (counter < length_s)
	{
		to_return[counter] = (*f)(counter, s[counter]);
		counter++;
	}
	to_return[counter] = '\0';
	return (to_return);
}
