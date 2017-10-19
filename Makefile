# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/21 11:32:23 by tpierron          #+#    #+#              #
#    Updated: 2017/10/18 17:31:25 by tpierron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = Nibbler

CC = clang++
SRC =	main.cpp \
		MlxDisplay.cpp

CFLAGS = -Wall -Wextra -Werror
OBJ_PATH = ./obj/
OBJ_NAME = $(SRC:.cpp=.o)

SDL = -L/Users/tpierron/.brew/lib -lSDL2
MLBX = -L/usr/lib -lmlx
SDL_PATH = -I/Users/tpierron/.brew/include/SDL2

OPENGL = -framework OpenGl -framework AppKit

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)
$(OBJ_PATH)%.o: %.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) -o $@ -c $(SDL_PATH) $< -std=c++11

$(NAME): $(OBJ)
	$(CC) $(SDL) $(MLBX) $(OPENGL) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

