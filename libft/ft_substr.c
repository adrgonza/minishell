/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:58:00 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 23:44:04 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char	*to_return;

	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	to_return = (char *)malloc((len + 1) * sizeof(char));
	if (to_return == 0)
		return (0);
	if (len == 0)
		ft_strlcpy(to_return, "", 1);
	else
		ft_strlcpy(to_return, (char *)(s + start), len + 1);
	return (to_return);
}
