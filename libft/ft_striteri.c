/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:56:22 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 23:38:58 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		length_s;
	int		counter;

	length_s = ft_strlen(s);
	counter = 0;
	while (counter < length_s)
	{
		(*f)(counter, s + counter);
		counter++;
	}
}
