# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 13:02:48 by okinnune          #+#    #+#              #
#    Updated: 2022/04/08 16:20:07 by okinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#NOTES:
#	For compiling fully from sources on Linux you need to install the following packages:
#	libx11-dev && libxext-dev 
#
INC=/usr/local/lib
INCLIB=$(INC)/../lib
CC=gcc
override CFLAGS+= -Ilibft -O2 -Wall -Werror -Wextra -g
NAME= FDF
SRC = main.c z_drawing.c vectors.c file_mapping.c \
	bresenham.c depthbuffer.c sorting.c \
	map_operations.c matrices.c drawing.c mt_drawing.c \
	loops.c errors.c file_nodereader.c \
	trimap.c
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
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(MLXFLAGS) -I. -I/libft

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
