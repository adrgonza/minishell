# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/04/29 22:53:27 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAIN = mix/main.c
NAME_DEBUG = minishell_debug

SRCS = mix/prompt.c mix/list_tkn.c mix/list_tkn2.c mix/init_exit.c \
mix/list_tkn3.c mix/list_env.c mix/list_env2.c mix/list_env3.c \
parsing/parsing.c parsing/check_std.c  parsing/get_args.c parsing/args_tools.c\
parsing/parsing_tools.c parsing/manage_quotes.c \
exec/ft_executer.c  exec/fork_exec.c exec/ft_exectkn.c exec/builtin.c \
exec/builtin2.c exec/builtin3.c

CC = cc

OBJS = ${SRCS:.c=.o}

MAINOBJ = ${MAIN:.c=.o}

CFLAGS = #-fsanitize=address -g #-Wall -Werror -Wextra
READLINE_FLAGS = -lreadline  #"-L/Users/adrgonza/.brew/opt/readline/lib/" #

all: $(NAME)

 $(NAME): $(OBJS) $(MAINOBJ) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(MAINOBJ) libft/libft.a $(READLINE_FLAGS) -o $@

$(NAMETEST): $(OBJS) $(TESTOBJ) libft/libft.a
	$(CC) $(CFLAGS)  $(OBJS) $(TESTOBJ) libft/libft.a $(READLINE_FLAGS) -o $@

$(NAME_DEBUG): $(SRCS) $(MAINOBJ) libft/libft.a
	$(CC) $(CFLAGS) -D DEBUG=1 -fdiagnostics-color=always -g $(SRCS) $(MAIN) $(READLINE_FLAGS) libft/libft.a -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJS) $(MAINOBJ) $(TESTOBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(TEST) $(NAME_DEBUG)
	make -C libft fclean

test: $(NAMETEST)

VS_debug: $(NAME_DEBUG)

re: fclean all

.PHONY: all clean fclean re bonus VS_debug
