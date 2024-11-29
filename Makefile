CC			=	gcc

NAME 		=	mysh

SRC			=	$(wildcard src/*.c) $(wildcard src/builtins/*.c) $(wildcard src/utils/*.c)

OBJ			=	$(SRC:.c=.o)

CFLAGS		=	-W -Wall -Wextra -g3

CPPFLAGS 	= 	-I./include/

all: $(NAME)

$(NAME): build $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIB)

clean:
		rm -f $(NAME)

fclean:	clean
		rm -f $(OBJ)

re:		fclean all

.PHONY:		all clean fclean re