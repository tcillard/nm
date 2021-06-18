SCURSOR = \033[s
RCURSOR = \033[u
ERASEL = \033[K

NAME=ft_nm

FLAGS = -Wall -Wextra -Werror -I

OBJECTS_DIR = ./objects
NM_OBJECTS_DIR = $(OBJECTS_DIR)

NM_FILES = nm.c \
	debug.c

INCLUDE_DIR = ./includes
SOURCE_DIR = ./sources
OBJECTS_FILES = $(NM_FILES:.c=.o)
OBJECTS_PATH = $(addprefix $(OBJECTS_DIR)/, $(OBJECTS_FILES))

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c
	@ echo "$(RCURSOR)$(ERASEL)\c"
	@ echo "$(SCURSOR)$(@F) \c"
	@ gcc $(FLAGS) $(INCLUDE_DIR) -c $< -o $@

$(NAME): dir $(OBJECTS_PATH)
	@ gcc $(FLAGS) $(INCLUDE_DIR) -o $(NAME) $(OBJECTS_PATH)
	@ echo "\nDONE"
 
.PHONY: all clean fclean re

all: $(NAME)

clean:
	@ rm -rf $(OBJECTS_DIR)

fclean: clean
	@ rm -rf $(NAME)

print: $(NM_OBJECTS_DIR)
	@ echo "ALL_FILES = $(OBJECTS_FILES)\n"

re: fclean all

dir:
	@ mkdir -p $(OBJECTS_DIR)