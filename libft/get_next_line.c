/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:26:08 by amejia            #+#    #+#             */
/*   Updated: 2023/02/21 00:41:48 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_line_from_left(char **left)
{
	char	*breakpoint;
	char	*before;
	char	*after;
	char	*old;

	breakpoint = ft_strchr(*left, '\n');
	if (breakpoint == 0)
		return (*left);
	before = ft_substr(*left, 0, (int)(breakpoint - *left + 1));
	after = ft_substr(breakpoint + 1, 0, ft_strlen(breakpoint + 1));
	old = *left;
	*left = after;
	free(old);
	return (before);
}

char	*read_from_file(int fd, char **left)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*old;
	int		k;
	int		bytes_read;

	k = -1;
	while (k++ < BUFFER_SIZE)
		buffer[k] = '\0';
	if (*left == 0)
		*left = ft_calloc(1, 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		old = *left;
		*left = ft_strjoin(*left, buffer);
		return (free(old), get_next_line(fd));
	}
	else if (bytes_read == -1 || !(ft_strlen(*left)))
	{
		free(*left);
		return (*left = 0, (char *)0);
	}
	old = ft_substr(*left, 0, ft_strlen(*left));
	free (*left);
	return (*left = 0, old);
}

char	*get_next_line(int fd)
{
	static char	*left[1024];

	if (fd < 0 || fd > 1023)
		return (0);
	if (left[fd] != 0 && ft_strchr(left[fd], '\n'))
		return (create_line_from_left(&left[fd]));
	else
		return (read_from_file(fd, &left[fd]));
}
