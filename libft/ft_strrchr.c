/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:57:32 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 14:34:03 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*end;

	end = (char *)(s + ft_strlen(s));
	while (end >= s)
	{
		if (*end == (char)c)
			return (end);
		if (end == s)
			break ;
		if (end > s)
			end--;
	}
	return (0);
}
