# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/04/18 00:31:56 by adrgonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAIN = mix/main.c
TESTMAIN = testmain.c
NAME_DEBUG = minishell_debug

SRCS = mix/prompt.c mix/list_tkn.c mix/list_tkn2.c parsing/parsing.c \
exec/ft_executer.c mix/init_exit.c parsing/get_args.c parsing/args_tools.c \

NAMETEST = testout

CC = cc
OBJS = ${SRCS:.c=.o}
MAINOBJ = ${MAIN:.c=.o}
TESTOBJ = ${TESTMAIN:.c=.o}

#CFLAGS = -Wall -Werror -Wextra
READLINE_FLAGS = -lreadline  #"-L/Users/adrgonza/.brew/opt/readline/lib/" #




all: $(NAME)

 $(NAME): $(OBJS) $(MAINOBJ) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(MAINOBJ) libft/libft.a $(READLINE_FLAGS) -o $@



$(NAMETEST): $(OBJS) $(TESTOBJ) libft/libft.a
	$(CC) $(CFLAGS)  $(OBJS) $(TESTOBJ) libft/libft.a $(READLINE_FLAGS) -o $@


$(NAME_DEBUG): $(SRCS) $(TESTMAIN) libft/libft.a
	$(CC) $(CFLAGS) -fdiagnostics-color=always -g $(SRCS) $(TESTMAIN) $(READLINE_FLAGS) libft/libft.a -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJS) $(MAINOBJ) $(TESTOBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(TEST)
	make -C libft fclean

test: $(NAMETEST)

VS_debug: $(NAME_DEBUG)

re: fclean all

.PHONY: all clean fclean re bonus
