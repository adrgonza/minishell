# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/04/05 17:30:26 by adrgonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = mix/main.c mix/prompt.c argv_generator.c ft_execchar.c\
CC = gcc
OBJS = ${SRCS:.c=.o}

#CFLAGS = -Wall -Werror -Wextra
READLINE_FLAGS = -lreadline #"-L/Users/adrgonza/.brew/opt/readline/lib/" #

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(READLINE_FLAGS) $(OBJS) libft/libft.a -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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
