/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:21:26 by amejia            #+#    #+#             */
/*   Updated: 2023/05/15 23:36:29 by amejia           ###   ########.fr       */
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

int	check_valid(int argc, char **argv)
{
	int	cnt[2];
	int	signs;

	cnt[0] = 0;
	while (cnt[0]++ < argc -1)
	{
		cnt[1] = 0;
		signs = 0;
		while (argv[cnt[0]][cnt[1]] != '\0')
		{
			if (argv[cnt[0]][cnt[1]] == '+' || argv[cnt[0]][cnt[1]] == '-')
			{
				signs ++;
				cnt[1]++;
			}
			else if (argv[cnt[0]][cnt[1]] == ' ' || argv[cnt[0]][cnt[1]] <= '9' \
				|| argv[cnt[0]][cnt[1]] >= '0')
				cnt[1]++;
			else
				return (1);
		}
		if (signs > 1 || !check_digit_str(argv[cnt[0]]))
			return (1);
	}
	return (0);
}
