# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 13:02:48 by okinnune          #+#    #+#              #
#    Updated: 2022/03/22 09:31:48 by okinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#NOTES:
#	For compiling fully from sources on Linux you need to install the following packages:
#	libx11-dev && libxext-dev 
#
INC=/usr/local/lib
INCLIB=$(INC)/../lib
CC=gcc
override CFLAGS+= -Wall -Werror -Wextra -Ilibft -g #-O2 -flto
NAME= mlx-test
SRC = main.c drawing.c vectors.c file_mapping.c \
	bresenham.c sorting.c freedom.c z_buffer.c	\
	map_operations.c matrices.c threading.c \
	loops.c errors.c file_nodereader.c
LIB = libft/libft.a
OBJ = $(SRC:.c=.o)

UNAME= $(shell uname)
ifeq ($(UNAME), Darwin)
MLXFLAGS = libmlx.dylib
else ifeq ($(UNAME), Linux)
override CFLAGS += -Imlx/Linux
MLXFLAGS =  -Imlx/Linux/ -I/usr/include -I/usr/lib/ mlx/Linux/libmlx.a -lm -lX11 -lXext
else
warning:
	@echo "Platform $(UNAME) not supported by FDF."
	exit 1
endif

all	:
	@echo "Compiling for platform: $(UNAME)."
	$(MAKE) $(NAME)


$(NAME)	:$(OBJ)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME)_$(UNAME) $(OBJ) $(LIB) $(MLXFLAGS) -I. -I/libft

extra	:
	$(MAKE) fclean
	$(MAKE) CFLAGS='-D EXTRA -pthread'

clean	:
	make -C libft clean
	rm -f $(OBJ) *~ core *.core

fclean	: clean
	rm -f $(NAME)

re	: fclean all

.PHONY: clean fclean extra re all warning
