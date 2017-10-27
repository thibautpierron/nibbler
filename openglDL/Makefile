# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2017/10/27 15:26:35 by mchevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

LIBNAME = OpenglDL.so

CC = clang++
SRC =	OpenglDL.cpp \
		Shader.class.cpp \
		Joint.class.cpp \
		Mesh.class.cpp \
		Model.class.cpp \

CFLAGS = -Wall -Wextra -Werror -O3 -std=c++11
OBJ_PATH = ./obj/
OBJ_NAME = $(SRC:.cpp=.o)

SDL = -L/Users/$(LOGNAME)/.brew/lib -lSDL2
SDL_PATH = -I/Users/$(LOGNAME)/.brew/include/SDL2

ASSIMP = -L/Users/$(LOGNAME)/.brew/lib -lassimp
ASSIMP_PATH = -I/Users/$(LOGNAME)/.brew/include/

GLM_PATH = -I/Users/$(LOGNAME)/.brew/include/glm

OPENGL = -framework OpenGl -framework AppKit

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(LIBNAME)
$(OBJ_PATH)%.o: %.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/classes 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/classes/model 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/classes/game 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) -o $@ -c $(SDL_PATH) $(ASSIMP_PATH) $(GLM_PATH) $< -std=c++11

$(LIBNAME): $(OBJ)
	$(CC) -shared -fPIC $(SDL) $(ASSIMP) $(OPENGL) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(LIBNAME)

re: fclean all
