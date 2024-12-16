CC			=	gcc

NAME 		=	mysh

SRC_DIR		=	src
BUILD_DIR	=	obj
LIB_DIR		=	lib/node
INCLUDE_DIR =	include $(LIB_DIR)/include

SRC			=	$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/builtins/*.c) $(wildcard $(SRC_DIR)/utils/*.c)
OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Flags généraux
CFLAGS 		=	-W -Wall -Wextra -Wshadow -Wconversion -pedantic
CPPFLAGS 	= 	$(addprefix -I, $(INCLUDE_DIR))
LDFLAGS		=	$(LIB_DIR)/libnode.a

# Debug and release flags
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
CFLAGS_RELEASE	=	-O2
CFLAGS_DEBUG	=	-g3 -O0

all: $(NAME)

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: re

# --suppressions=valgrind.supp
valgrind: debug
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

release: CFLAGS += $(CFLAGS_RELEASE)
release: re

$(NAME): $(OBJ) $(LIB_DIR)/libnode.a
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIB_DIR)/libnode.a:
	$(MAKE) -C $(LIB_DIR)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug release clean fclean re
