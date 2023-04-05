/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:56:35 by amejia            #+#    #+#             */
/*   Updated: 2023/01/17 14:06:25 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t dstsize)
{
	unsigned int	len_dest;
	unsigned int	len_src;

	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (dstsize < len_dest)
		return (len_src + dstsize);
	while (*dest != '\0' )
		dest++;
	ft_strlcpy(dest, src, dstsize - len_dest);
	return (len_src + len_dest);
}
