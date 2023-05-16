/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_esc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:55:57 by amejia            #+#    #+#             */
/*   Updated: 2023/05/15 22:34:16 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_lines_esc(char *text, char find)
{
	int		counter;
	char	*orig;

	counter = 0;
	orig = text;
	while (*text != '\0')
	{
		if (*text != find && (*(text + 1) == find || *(text + 1) == '\0') && \
		!((text - orig) > 1 && (*(text - 1)) == '\\'))
			counter++;
		text++;
	}
	return (counter);
}

static int	ft_split_loop_esc(char **matrix, char *s, int n_lines, char c)
{
	int		length;
	int		iterator;
	char	*next_position;

	iterator = 0;
	while (iterator < n_lines)
	{
		next_position = ft_min_str(ft_strchr_esc(s, c), ft_strchr(s, '\0'));
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

char	**ft_split_esc(char *s, char c)
{
	char	**matrix;
	int		n_lines;
	int		error_asign;

	n_lines = count_lines_esc (s, c);
	matrix = (char **) ft_calloc ((n_lines + 1), sizeof (char *));
	if (matrix == 0)
		return (0);
	error_asign = ft_split_loop_esc(matrix, s, n_lines, c);
	if (error_asign == -1)
		return (matrix);
	while (error_asign-- >= 0)
		free(matrix[error_asign]);
	free(matrix);
	return (0);
}
