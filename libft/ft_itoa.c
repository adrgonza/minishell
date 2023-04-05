/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:54:02 by amejia            #+#    #+#             */
/*   Updated: 2023/02/21 00:50:40 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	memory_asignation(char **to_return, int n, int *string_size)
{
	*string_size = pseudolog10(n);
	*to_return = (char *)ft_calloc((*string_size + 1), sizeof(char));
	if (*to_return == 0)
		return (0);
	return (1);
}

int	special_case(char **to_return, int n, int string_size)
{
	if (n == -2147483647 - 1)
	{
		ft_strlcpy(*to_return, "-2147483648", string_size + 1);
		return (1);
	}
	else
		return (0);
}

char	*ft_itoa(int n)
{
	char	*to_return;
	char	*work_head;
	int		string_size;
	int		counter;

	counter = 0;
	if (!memory_asignation(&to_return, n, &string_size))
		return (0);
	work_head = to_return + string_size - 1;
	if (special_case(&to_return, n, string_size))
		return (to_return);
	if (n < 0)
	{
		n = -n;
		*to_return = '-';
		counter++;
	}
	while (counter < string_size)
	{
		*work_head = n % 10 + '0';
		n = n / 10;
		counter ++;
		work_head--;
	}
	return (to_return);
}
