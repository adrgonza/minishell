/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tags_pxX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:04:49 by amejia            #+#    #+#             */
/*   Updated: 2023/01/29 20:57:45 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	tag_p(va_list va_ptr, int *nchar)
{
	void	*j;

	j = va_arg(va_ptr, void *);
	write(1, "0x", 2);
	ft_putnbr_base_fd_ul((unsigned long)j, "0123456789abcdef", 1);
	*nchar += pseudologbase_u((unsigned long)j, 16) + 2;
}

void	tag_x(va_list va_ptr, int *nchar)
{
	unsigned int	j;

	j = va_arg(va_ptr, unsigned int);
	ft_putnbr_base_fd_u(j, "0123456789abcdef", 1);
	*nchar += pseudologbase_u(j, 16);
}

void	tag_ux(va_list va_ptr, int *nchar)
{
	unsigned int	j;

	j = va_arg(va_ptr, unsigned int);
	ft_putnbr_base_fd_u(j, "0123456789ABCDEF", 1);
	*nchar += pseudologbase_u(j, 16);
}
