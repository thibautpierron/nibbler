# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2017/11/03 13:28:51 by tpierron         ###   ########.fr        #
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
		Skybox.cpp \

INCLUDES =	OpenglDL.hpp\
			Shader.class.hpp\
			Joint.class.hpp\
			Mesh.class.hpp\
			Model.class.hpp\
			Skybox.hpp

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
	$(CC) $(CFLAGS) -o $@ -c $(SDL_PATH) $(ASSIMP_PATH) $(GLM_PATH) $< -std=c++11

$(LIBNAME): $(OBJ)
	$(CC) -shared -fPIC $(SDL) $(ASSIMP) $(OPENGL) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_NAME)

fclean: clean
	rm -f $(LIBNAME)

re: fclean all
