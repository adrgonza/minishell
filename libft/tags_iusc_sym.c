/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tags_iusc_sym.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:01:18 by amejia            #+#    #+#             */
/*   Updated: 2023/01/29 20:54:52 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	tag_i(va_list va_ptr, int *nchar)
{
	int	j;

	j = va_arg(va_ptr, int);
	ft_putnbr_fd(j, 1);
	*nchar += pseudolog10(j);
}

void	tag_u(va_list va_ptr, int *nchar)
{
	unsigned int	j;

	j = va_arg(va_ptr, unsigned int);
	ft_putunbr_fd(j, 1);
	*nchar += pseudolog10_u(j);
}

void	tag_s(va_list va_ptr, int *nchar)
{
	char	*j;

	j = va_arg(va_ptr, char *);
	if (j == 0)
	{
		ft_putstr_fd("(null)", 1);
		*nchar += 6;
		return ;
	}
	ft_putstr_fd(j, 1);
	*nchar += ft_strlen(j);
}

void	tag_c(va_list va_ptr, int *nchar)
{
	ft_putchar_fd(va_arg(va_ptr, int), 1);
	(*nchar)++;
}

void	tag_sym(int *nchar)
{
	write(1, "%", 1);
	(*nchar)++;
}
