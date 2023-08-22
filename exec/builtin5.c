/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:21:26 by amejia            #+#    #+#             */
/*   Updated: 2023/05/25 16:44:46 by adrgonza         ###   ########.fr       */
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
