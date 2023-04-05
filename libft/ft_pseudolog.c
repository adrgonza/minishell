/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudolog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:35:53 by amejia            #+#    #+#             */
/*   Updated: 2023/01/29 20:59:47 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	pseudolog10(int n)
{
	if (n == -2147483648)
		return (11);
	if (n < 0)
		return (1 + pseudolog10(-n));
	if (n <= 9)
		return (1);
	return (1 + pseudolog10(n / 10));
}

int	pseudolog10_u(unsigned int n)
{
	if (n <= 9)
		return (1);
	return (1 + pseudolog10_u(n / 10));
}

int	pseudologbase(long n, long base)
{
	if (base < 2)
		return (-1);
	if (n < 0)
		return (1 + pseudologbase(-n, base));
	if (n < base)
		return (1);
	return (1 + pseudologbase(n / base, base));
}

int	pseudologbase_u(unsigned long n, long base)
{
	if (n < (unsigned long)base)
		return (1);
	return (1 + pseudologbase_u(n / base, base));
}
