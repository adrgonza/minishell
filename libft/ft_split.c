/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:55:57 by amejia            #+#    #+#             */
/*   Updated: 2023/03/14 20:34:26 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_lines(char *text, char find)
{
	int	counter;

	counter = 0;
	while (*text != '\0')
	{
		if (*text != find && (*(text + 1) == find || *(text + 1) == '\0'))
			counter++;
		text++;
	}
	return (counter);
}

char	*ft_min_str(char *s1, char *s2)
{
	if (s1 == 0 && s2 == 0)
		return (0);
	if (s1 == 0)
		return (s2);
	if (s2 == 0)
		return (s1);
	if (s1 < s2)
		return (s1);
	return (s2);
}

static int	ft_split_loop(char **matrix, char *s, int n_lines, char c)
{
	int		length;
	int		iterator;
	char	*next_position;

	iterator = 0;
	while (iterator < n_lines)
	{
		next_position = ft_min_str(ft_strchr(s, c), ft_strchr(s, '\0'));
		length = next_position - s;
		if (length == 0)
		{
			s = next_position + 1;
			continue ;
		}
		matrix[iterator] = (char *)malloc(length + 1);
		if (matrix[iterator] == 0)
			return (iterator);
		ft_strlcpy(matrix[iterator], s, length + 1);
		if (*next_position != '\n')
			s = next_position + 1;
		iterator++;
	}
	return (-1);
}

char	**ft_split(char *s, char c)
{
	char	**matrix;
	int		n_lines;
	int		error_asign;

	n_lines = count_lines (s, c);
	matrix = (char **) ft_calloc ((n_lines + 1), sizeof (char *));
	if (matrix == 0)
		return (0);
	error_asign = ft_split_loop(matrix, s, n_lines, c);
	if (error_asign == -1)
		return (matrix);
	while (error_asign-- >= 0)
		free(matrix[error_asign]);
	free(matrix);
	return (0);
}

void	ft_free_split(char **split)
{
	int	ct;

	ct = 0;
	while (split[ct] != 0)
	{
		free(split[ct]);
		ct++;
	}
	free(split);
}
