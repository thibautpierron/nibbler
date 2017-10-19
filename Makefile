# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/21 11:32:23 by tpierron          #+#    #+#              #
#    Updated: 2017/10/19 13:42:33 by tpierron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = Nibbler
LIB1_NAME = OpenglDL.so

CC = clang++
MAIN_SRC = main.cpp
#LIB1_SRC = mlxDL/MlxDisplay.cpp
LIB1_SRC = openglDL/OpenglDL.cpp

CFLAGS = -Wall -Wextra -Werror
OBJ_PATH = ./obj/
OBJ_NAME = $(MAIN_SRC:.cpp=.o)

#MLX = -L/usr/lib -lmlx
OPENGL = -framework OpenGl -framework AppKit

SDL = -L/Users/tpierron/.brew/lib -lSDL2
SDL_PATH = -I/Users/tpierron/.brew/include/SDL2

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: lib1 $(NAME)

$(OBJ_PATH)%.o: %.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) -o $@ -c $< -std=c++11

$(NAME): $(OBJ)
	$(CC) $(SDL) $(CFLAGS) -o $@ $^

# lib1:
# 	$(CC) -shared -fPIC -o $(LIB1_NAME) $(LIB1_SRC) $(MLX) $(OPENGL) $(CFLAGS)

lib1:
	$(CC) -shared -fPIC -o $(LIB1_NAME) $(LIB1_SRC) $(SDL) $(SDL_PATH) $(OPENGL) $(CFLAGS)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME) $(LIB1_NAME)

re: fclean all

