# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 17:57:56 by okinnune          #+#    #+#              #
#    Updated: 2022/04/21 14:27:17 by okinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
HEADER= libft.h
FILES= ft_abs.c ft_atoi.c ft_bzero.c ft_digitcount.c ft_isalnum.c ft_isalpha.c\
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstapp.c \
	ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
	ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c\
	ft_memmove.c ft_memset.c ft_pow.c ft_putchar.c ft_putchar_fd.c \
	ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
	ft_putstr_fd.c ft_sqrt.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
	ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_strfill.c ft_striter.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
	ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
	ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
	ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_isspace.c \
	ft_ftoa.c ft_memdup.c ft_clamp.c ft_clampf.c ft_min_max.c \
	ft_get_next_line.c ft_strscrape.c
FLAGS= -Wall -Wextra -Werror -O2 -c -g
SRCS= $(addprefix src/, $(FILES))
#SRCS+=$(V_SRCS)
OBJS= $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS):
	gcc $(FLAGS) $(HEADER) $(SRCS) -I.

#$(V_OBJS):
#	gcc $(FLAGS) $(HEADER) $(V_SRCS) -I.

ac: all clean

clean:
	rm -f $(OBJS)
	rm -f *h.gch

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: all ac clean fclean re