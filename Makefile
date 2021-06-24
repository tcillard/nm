# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 14:53:04 by tcillard          #+#    #+#              #
#    Updated: 2021/06/24 22:59:40 by tcillard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SCURSOR = \033[s
RCURSOR = \033[u
ERASEL = \033[K

NAME=ft_nm

FLAGS = -Wall -Wextra -Werror

OBJECTS_DIR = ./objects
NM_OBJECTS_DIR = $(OBJECTS_DIR)

NM_FILES = nm.c \
	checkElf.c \
	treatSectionTable32Bits.c \
	treatSectionTable64Bits.c \
	structTools.c \
	tools.c \
	symbolesListTools.c

INCLUDE_DIR = -I ./includes
SOURCE_DIR = ./sources
OBJECTS_FILES = $(NM_FILES:.c=.o)
OBJECTS_PATH = $(addprefix $(OBJECTS_DIR)/, $(OBJECTS_FILES))


$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c
	gcc $(FLAGS) $(INCLUDE_DIR) -c $< -o $@


$(NAME): dir $(OBJECTS_PATH)
	gcc $(FLAGS) $(INCLUDE_DIR) -o $(NAME) $(OBJECTS_PATH)
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