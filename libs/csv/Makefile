CC		:=	gcc
NAME	:=	libcsv.a
CFLAGS	:=	-Wall -Wextra -Werror -ansi -pedantic -fno-builtin -O3 -I./include
SRC		:=	$(wildcard src/*.c)
INC		:=	include/csv_parser.h
INC_FOL	:=	../../include/
OBJ		:=	$(SRC:.c=.o)

all: $(NAME) make_include

$(NAME): $(OBJ) make_include
	ar rcs $(NAME) $(OBJ)
	cp $(NAME) ..

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

make_include:
	mkdir -p $(INC_FOL)
	cp $(INC) $(INC_FOL)

clean:
	rm -rf $(NAME) ../$(NAME)

fclean: clean
	rm -rf $(OBJ)

re: fclean all

.SILENT:

.PHONY: all clean fclean re