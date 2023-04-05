/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:57:23 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 14:32:41 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	substring_comparison(char *s1, char *s2, size_t n)
{
	unsigned int	n2;
	char			*s1_aux;
	char			*s2_aux;

	n2 = n;
	s1_aux = s1;
	s2_aux = s2;
	while (*s1_aux == *s2_aux && n2 > 0)
	{
		if (*(s2_aux + 1) == '\0')
			return (1);
		if (*s1_aux == '\0')
			return (0);
		s1_aux++;
		s2_aux++;
		n2--;
	}
	return (3);
}

char	*ft_strnstr(char *s1, char *s2, size_t n)
{
	int		sub_s_comp;

	if (ft_strlen(s2) == 0)
		return (s1);
	while (*s1 != '\0' && n > 0)
	{
		if (*s1 == *s2)
		{
			sub_s_comp = substring_comparison(s1, s2, n);
			if (sub_s_comp == 1)
				return (s1);
			if (sub_s_comp == 2)
				return (0);
		}
		s1++;
		n--;
	}
	return (0);
}
