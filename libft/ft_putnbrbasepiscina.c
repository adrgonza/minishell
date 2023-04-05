/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbasepiscina.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 03:07:11 by amejia            #+#    #+#             */
/*   Updated: 2023/02/18 03:15:33 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *str)
{
	char	*str2;

	str2 = str;
	if (ft_strlen(str) < 2)
		return (0);
	while (*str2 != '\0')
	{
		if (*str2 == '+' || *str2 == '-')
			return (0);
		str2++;
	}
	while (*str != '\0')
	{
		str2 = str + 1;
		while (*str2 != '\0')
		{
			if (*str == *str2)
				return (0);
			str2++;
		}
		str++;
	}
	return (1);
}

static void	ft_putnbr_base_spl_fd(long long nbr, char *base, int base_n, int fd)
{
	if (nbr < 0)
	{
		write(1, "-", 1);
		ft_putnbr_base_spl_fd(-nbr, base, base_n, fd);
	}
	if (nbr < base_n)
		write(fd, base + nbr, 1);
	else
	{
		ft_putnbr_base_spl_fd(nbr / base_n, base, base_n, fd);
		ft_putnbr_base_spl_fd(nbr % base_n, base, base_n, fd);
	}
}

void	ft_putnbr_base_fd(long long nbr, char *base, int fd)
{
	long long	base_n;

	base_n = ft_strlen(base);
	if (!check_base(base))
		return ;
	ft_putnbr_base_spl_fd(nbr, base, base_n, fd);
}
