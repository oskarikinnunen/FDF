INC=/usr/local/lib
HT=Linux
DOCP=do_cp



INCLIB=$(INC)/../lib

CC=gcc

CFLAGS= -I$(INC) -I.. -I/libft

NAME= mlx-test
SRC = main.c
LIB = libft/libft.a
OBJ = $(SRC:.c=.o)

all	:$(NAME)

$(NAME)	:$(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(LIB) -L.. -lmlx -lbsd -L$(INCLIB) -lXext -lX11 -lm $(CFLAGS)

clean	:
	rm -f $(NAME) $(OBJ) *~ core *.core


re	: clean all
