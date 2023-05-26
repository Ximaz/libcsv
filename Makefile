CC		:=	gcc
NAME	:=	csv_parser
SRC		:=	$(wildcard src/*.c)
CFLAGS	:=	-Wall -Wextra -Werror -ansi -pedantic -fno-builtin -O3 -I./include -L./libs
LIBS	:=	-lcsv
OBJ		:=	$(SRC:.c=.o)
VFLAGS	:=	--track-origins=yes --show-leak-kinds=all	\
			--leak-check=full -s --trace-children=yes	\
			--read-inline-info=yes --read-var-info=yes	\
			--errors-for-leak-kinds=all

all:	$(NAME)

libs:
	make -sC libs

$(NAME):	libs	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean:
	rm -rf $(OBJ)
	make -sC libs clean

fclean:	clean
	rm -rf $(NAME)
	make -sC libs fclean

re:	fclean	all

valgrind: all
	valgrind $(VFLAGS) ./$(NAME)

.SILENT:

.PHONY:	all	clean	fclean	re