/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:46:05 by amejia            #+#    #+#             */
/*   Updated: 2023/01/29 21:00:56 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base_spl_fd_u(unsigned int n, char *base, int bn, int fd)
{
	if (n < (unsigned int)bn)
		write(fd, base + n, 1);
	else
	{
		ft_putnbr_base_spl_fd_u(n / bn, base, bn, fd);
		ft_putnbr_base_spl_fd_u(n % bn, base, bn, fd);
	}
}

void	ft_putnbr_base_fd_u(unsigned int nbr, char *base, int fd)
{
	unsigned int	base_n;

	base_n = ft_strlen(base);
	if (!check_base(base))
		return ;
	ft_putnbr_base_spl_fd_u(nbr, base, base_n, fd);
}

void	ft_putnbr_base_spl_fd_ul(unsigned long n, char *b, int bn, int fd)
{
	if (n < (unsigned long)bn)
		write(fd, b + n, 1);
	else
	{
		ft_putnbr_base_spl_fd_ul(n / bn, b, bn, fd);
		ft_putnbr_base_spl_fd_ul(n % bn, b, bn, fd);
	}
}

void	ft_putnbr_base_fd_ul(unsigned long nbr, char *base, int fd)
{
	unsigned int	base_n;

	base_n = ft_strlen(base);
	if (!check_base(base))
		return ;
	ft_putnbr_base_spl_fd_ul(nbr, base, base_n, fd);
}
