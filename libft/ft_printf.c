/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:05:59 by amejia            #+#    #+#             */
/*   Updated: 2023/01/29 23:46:57 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *string, ...)
{
	int		nchar;
	va_list	va_ptr;

	nchar = 0;
	va_start(va_ptr, string);
	process_string((char *)string, va_ptr, &nchar);
	return (nchar);
}

void	process_string(char *str, va_list va_ptr, int *nchar)
{
	char			*tag_pos;
	unsigned int	np_char;

	tag_pos = ft_strchr(str, '%');
	if (tag_pos != 0)
		np_char = (unsigned int)(tag_pos - str);
	else
		np_char = ft_strlen(str);
	*nchar += np_char;
	ft_putnstr_fd(str, 1, np_char);
	if (tag_pos != 0)
	{
		tag_pos = tag_process(tag_pos, va_ptr, nchar);
		process_string(tag_pos, va_ptr, nchar);
	}
}

char	*tag_process(char *tag_pos, va_list va_ptr, int *nchar)
{
	char	tag;

	tag_pos++;
	tag = *(tag_pos);
	if (tag == 'i' || tag == 'd')
		tag_i(va_ptr, nchar);
	if (tag == 'c')
		tag_c(va_ptr, nchar);
	if (tag == 's')
		tag_s(va_ptr, nchar);
	if (tag == '%')
		tag_sym(nchar);
	if (tag == 'p')
		tag_p(va_ptr, nchar);
	if (tag == 'x')
		tag_x(va_ptr, nchar);
	if (tag == 'X')
		tag_ux(va_ptr, nchar);
	if (tag == 'u')
		tag_u(va_ptr, nchar);
	return (tag_pos++, tag_pos);
}
