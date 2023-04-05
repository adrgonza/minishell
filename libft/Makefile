# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 19:16:14 by amejia            #+#    #+#              #
#    Updated: 2023/03/13 22:31:08 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

SRCS = ft_atoi.c ft_memchr.c ft_split.c ft_strncmp.c ft_bzero.c ft_memcmp.c \
ft_strchr.c ft_strnstr.c ft_calloc.c ft_memcpy.c ft_strdup.c ft_strrchr.c ft_isalnum.c \
ft_memmove.c ft_striteri.c ft_strtrim.c ft_isalpha.c ft_memset.c ft_strjoin.c ft_substr.c \
ft_isascii.c ft_putchar_fd.c ft_strlcat.c ft_tolower.c ft_isdigit.c ft_putendl_fd.c ft_strlcpy.c \
ft_toupper.c ft_isprint.c ft_putnbr_fd.c ft_strlen.c ft_itoa.c ft_putstr_fd.c \
ft_strmapi.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_printf.c ft_pseudolog.c ft_putnbrbase_int.c \
ft_putnbrbase_long.c tags_iusc_sym.c tags_pxX.c \
ft_value_swap.c get_next_line.c ft_abs.c ft_split_esc.c ft_delete_char.c
OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

INCLUDE = libft.h

all: $(NAME)  

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	ar -crs $(NAME) $@
	
bonus: $(NAME) $(BONUS_OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	ar -crs $(NAME) $@ 

$(NAME): ${OBJS}

clean: 
	rm -f ${OBJS} $(BONUS_OBJS)

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

