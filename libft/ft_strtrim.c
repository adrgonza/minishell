/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:57:38 by amejia            #+#    #+#             */
/*   Updated: 2023/01/18 18:25:34 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*end;
	char	*s2;

	while (ft_strchr(set, (int)(*s1)) && *s1 != '\0')
		s1++;
	if (ft_strlen(s1) == 0)
		return (ft_strdup((char *)s1));
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (ft_strchr(set, (int)(*end)) && end - s1 > 0)
	{
		end--;
	}
	s2 = ft_calloc((unsigned int)(end - s1) + 2, sizeof(char));
	if (s2 == 0)
		return (0);
	ft_strlcpy(s2, (char *)s1, (unsigned int)(end - s1) + 2);
	if (s2 == 0)
		return (0);
	return (s2);
}
