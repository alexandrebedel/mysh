CC			=	gcc

NAME 		=	mysh

SRC_DIR		=	src
BUILD_DIR	=	obj
INCLUDE_DIR =	include

SRC			=	$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/builtins/*.c) $(wildcard $(SRC_DIR)/utils/*.c)
OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Flags généraux
CFLAGS 		=	-W -Wall -Wextra -Wshadow -Wconversion -pedantic
CPPFLAGS 	= 	-I$(INCLUDE_DIR)

# Debug and release flags
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
CFLAGS_RELEASE	=	-O2
CFLAGS_DEBUG	=	-g3 -O0

all: $(NAME)

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: re

release: CFLAGS += $(CFLAGS_RELEASE)
release: re

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug release clean fclean re