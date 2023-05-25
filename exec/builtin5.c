/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:21:26 by amejia            #+#    #+#             */
/*   Updated: 2023/05/23 22:55:44 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_digit_str(char *str)
{
	int	neg;

	neg = 0;
	if (*str == '-')
		neg = 1;
	if (*str == '-')
		str++;
	while (*str == ' ')
		str++;
	if (ft_strlen(str) > 10)
		return (0);
	else if (ft_strlen(str) < 10)
		return (1);
	else if (neg == 1 && (ft_strncmp(str, "2147483648", -1) > 0))
		return (0);
	else if (ft_strncmp(str, "2147483647", -1) > 0)
		return (0);
	return (1);
}

int	check_valid(char *enter)
{
	int	cnt[2];
	int	signs;

	cnt[1] = 0;
	signs = 0;
	if (ft_strlen(enter) == 0)
		return (1);
	while (enter[cnt[1]] != '\0')
	{
		if (enter[cnt[1]] == '+' || enter[cnt[1]] == '-')
		{
			signs ++;
			cnt[1]++;
		}
		else if (enter[cnt[1]] == ' ' || (enter[cnt[1]] <= '9' \
			&& enter[cnt[1]] >= '0'))
			cnt[1]++;
		else
			return (1);
	}
	if (signs > 1 || !check_digit_str(enter))
		return (1);
	return (0);
}
