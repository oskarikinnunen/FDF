# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 13:02:48 by okinnune          #+#    #+#              #
#    Updated: 2022/02/18 16:34:39 by okinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC=/usr/local/lib
#HT=Linux
#DOCP=do_cp
INCLIB=$(INC)/../lib
CC=gcc
NAME= mlx-test
SRC = main.c text.c math.c vectors.c commands.c drawing.c cocoaconvert.c image.c
LIB = libft/libft.a
OBJ = $(SRC:.c=.o)
UNAME= $(shell uname)

MLXLIB = libmlx.dylib
ifeq ($(UNAME), Linux)
MLXLIB = mlx/Linux/libmlx.a
endif
#LINUX : 

#CFLAGS= -I$(INC) -I.. -I/libft
#$(CC) -o $(NAME) $(OBJ) -L.. -lmlx -lbsd -L$(INCLIB) -lXext -lX11 -lm $(LIB) $(CFLAGS)

#Linux flags = X11, lm

all	:$(NAME)

$(NAME)	:$(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(LIB) -I. $(MLXLIB) -I/usr/include -lm -lX11 -lXext -I/libft -I/mlx/Linux -g

clean	:
	make -C libft clean
	rm -f $(OBJ) *~ core *.core

fclean	: clean
	rm -f $(NAME)

re	: clean all
