# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/05/19 20:26:54 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAIN = mix/main.c
NAME_DEBUG = minishell_debug

SRCS = mix/prompt.c mix/list_tkn.c mix/list_tkn2.c mix/init_exit.c \
mix/list_tkn3.c mix/list_env.c mix/list_env2.c mix/list_env3.c \
mix/signals.c \
parsing/parsing.c parsing/get_args.c parsing/args_tools.c parsing/check_std.c\
parsing/parsing_tools.c parsing/manage_quotes.c parsing/get_things.c \
parsing/var_expansion.c parsing/args_tools2.c parsing/parsing_tools2.c \
exec/ft_executer.c  exec/fork_exec.c exec/ft_exectkn.c exec/builtin.c \
exec/builtin2.c exec/builtin3.c exec/builtin4.c exec/builtin5.c exec/heredoc.c

CC = cc

OBJS = ${SRCS:.c=.o}

MAINOBJ = ${MAIN:.c=.o}

CFLAGS = -I/Users/amejia/minishell/homebrew/opt/readline/include -fsanitize=address -g #-Wall -Werror -Wextra
LDFLAGS = -L/Users/amejia/minishell/homebrew/opt/readline/lib -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(MAINOBJ) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(MAINOBJ) libft/libft.a $(LDFLAGS) -o $@

$(NAMETEST): $(OBJS) $(TESTOBJ) libft/libft.a
	$(CC) $(CFLAGS)  $(OBJS) $(TESTOBJ) libft/libft.a $(LDFLAGS) -o $@

$(NAME_DEBUG): $(SRCS) $(MAINOBJ) libft/libft.a
	$(CC) $(CFLAGS) -D DEBUG=1 -fdiagnostics-color=always -g $(SRCS) $(MAIN) $(LDFLAGS) libft/libft.a -o $@

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
