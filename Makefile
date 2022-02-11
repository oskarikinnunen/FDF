# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 13:02:48 by okinnune          #+#    #+#              #
#    Updated: 2022/02/11 14:56:01 by okinnune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC=/usr/local/lib
#HT=Linux
#DOCP=do_cp
INCLIB=$(INC)/../lib
CC=gcc
NAME= mlx-test
SRC = main.c text.c math.c vectors.c commands.c drawing.c cocoaconvert.c
LIB = libft/libft.a
OBJ = $(SRC:.c=.o)

#LINUX : 

#CFLAGS= -I$(INC) -I.. -I/libft
#$(CC) -o $(NAME) $(OBJ) -L.. -lmlx -lbsd -L$(INCLIB) -lXext -lX11 -lm $(LIB) $(CFLAGS)

all	:$(NAME)

$(NAME)	:$(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(LIB) -I. libmlx.dylib -I/libft -I/mlx

clean	:
	make -C libft clean
	rm -f $(OBJ) *~ core *.core


re	: clean all
