/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:58:11 by amejia            #+#    #+#             */
/*   Updated: 2023/05/15 22:34:40 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
		return (c + 'a' - 'A');
	return (c);
}

char	*ft_strtolower(char *str)
{
	unsigned int	ct;
	char			*to_return;

	to_return = ft_strdup(str);
	ct = 0;
	while (ct < ft_strlen(to_return))
	{
		to_return[ct] = ft_tolower(to_return[ct]);
		ct++;
	}
	return (to_return);
}
