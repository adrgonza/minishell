# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/03/14 14:49:09 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =  argv_generator.c ft_execchar.c prompt.c main.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $@

libft/libft.a:
	make -C libft

clean: 
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG) $(NAME_CHECKER)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re debug bonus