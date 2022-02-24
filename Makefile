# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 13:02:48 by okinnune          #+#    #+#              #
#    Updated: 2022/02/24 03:23:35 by okinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#NOTES:
#	For compiling fully from sources on Linux you need to install the following packages:
#	libx11-dev && libxext-dev
#
INC=/usr/local/lib
#HT=Linux
#DOCP=do_cp
INCLIB=$(INC)/../lib
CC=gcc
NAME= mlx-test
SRC = main.c text.c math.c vectors.c commands.c drawing.c cocoaconvert.c image.c file_mapping.c
LIB = libft/libft.a
OBJ = $(SRC:.c=.o)
UNAME= $(shell uname)

MLXLIB = libmlx.dylib
ifeq ($(UNAME), Linux)
MLXLIB = mlx/Linux/libmlx.a -I/usr/include -I/usr/lib/ -lm -lX11 -lXext -Imlx/Linux/
endif
#LINUX : 

#CFLAGS= -I$(INC) -I.. -I/libft
#$(CC) -o $(NAME) $(OBJ) -L.. -lmlx -lbsd -L$(INCLIB) -lXext -lX11 -lm $(LIB) $(CFLAGS)

#Linux flags = X11, lm

all	:$(NAME)

$(NAME)	:$(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(MLXLIB) -I. -I/libft -g

clean	:
	make -C libft clean
	rm -f $(OBJ) *~ core *.core

fclean	: clean
	rm -f $(NAME)

re	: clean all
