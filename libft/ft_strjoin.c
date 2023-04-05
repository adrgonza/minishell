/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:56:28 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 14:05:15 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*to_return;

	to_return = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (to_return == 0)
		return (0);
	ft_strlcpy(to_return, (char *)s1, -1);
	ft_strlcat(to_return, (char *)s2, -1);
	return (to_return);
}
