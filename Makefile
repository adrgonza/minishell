# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/03/15 17:16:58 by adrgonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#15 march
#added readline library compilation
#added readline flag
#added .o and .c 

NAME = minishell

SRCS =  argv_generator.c ft_execchar.c prompt.c main.c
CC = gcc
OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra
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
