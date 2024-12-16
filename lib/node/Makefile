# Compiler and Flags
CC          =	gcc
CFLAGS      =	-Wall -Wextra -Werror -std=c99
CPPFLAGS    =	-Iinclude
AR          =	ar rcs

SRC_DIR     =	src
INCLUDE_DIR =	include
OBJ_DIR     =	obj

SRC         = $(wildcard $(SRC_DIR)/*.c)
OBJ         = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB         = libnode.a

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(LIB)

re: fclean all

.PHONY: all clean fclean re