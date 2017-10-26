# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/21 11:32:23 by tpierron          #+#    #+#              #
#    Updated: 2017/10/26 17:25:14 by mchevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = Nibbler
LIB1_NAME = OpenglDL.so

CC = clang++
MAIN_SRC =	main.cpp \
			Game.cpp \
			frameTimer.class.cpp

# LIB1_SRC = openglDL/OpenglDL.cpp \
# 			openglDL/Shader.class.cpp \
# 			openglDL/model/Joint.class.cpp \
# 			openglDL/model/Mesh.class.cpp \
# 			openglDL/model/Model.class.cpp \


# DL STB_IMAGE !!!!!!!!!!!!!!!!!!!!!!

CFLAGS = -Wall -Wextra -Werror
OBJ_PATH = ./obj/
OBJ_NAME = $(MAIN_SRC:.cpp=.o)

# OPENGL = -framework OpenGl -framework AppKit

# SDL = -L/Users/$(LOGNAME)/.brew/lib -lSDL2
# SDL_PATH = -I/Users/$(LOGNAME)/.brew/include/SDL2
# GLM = -L/Users/$(LOGNAME)/.brew/lib -lglm
# GLM_PATH = -I/Users/$(LOGNAME)/.brew/include/glm
# ASS = -L/Users/$(LOGNAME)/.brew/lib -lassimp
# ASS_PATH = -I/Users/$(LOGNAME)/.brew/include/

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)#lib1 $(NAME)

$(OBJ_PATH)%.o: %.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) -o $@ -c $< -std=c++11

$(NAME): $(OBJ)
	$(CC) $(SDL) $(CFLAGS) -o $@ $^

# lib1:
	# $(CC) -shared -fPIC -o $(LIB1_NAME) $(LIB1_SRC) $(SDL) $(SDL_PATH) $(ASS) $(ASS_PATH)  $(GLM_PATH) $(OPENGL) $(CFLAGS) -std=c++11

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME) $(LIB1_NAME)

re: fclean all

