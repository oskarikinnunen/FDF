# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 13:02:48 by okinnune          #+#    #+#              #
#    Updated: 2022/03/16 14:52:08 by okinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#NOTES:
#	For compiling fully from sources on Linux you need to install the following packages:
#	libx11-dev && libxext-dev 
#
INC=/usr/local/lib
INCLIB=$(INC)/../lib
CC=gcc -g -fstack-protector-all
NAME= mlx-test
SRC = main.c drawing.c vectors.c file_mapping.c hooks.c bresenham.c sorting.c freedom.c z_buffer.c
LIB = libft/libft.a
OBJ = $(SRC:.c=.o)
UNAME= $(shell uname)

MLXLIB = libmlx.dylib
ifeq ($(UNAME), Linux)
MLXLIB = mlx/Linux/libmlx.a -I/usr/include -I/usr/lib/ -lm -lX11 -lXext -Imlx/Linux/
endif

all	:$(NAME)

$(NAME)	:$(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(MLXLIB) -I. -I/libft -g

clean	:
#	make -C libft clean
	rm -f $(OBJ) *~ core *.core

fclean	: clean
	rm -f $(NAME)

re	: clean all
