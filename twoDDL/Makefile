# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 11:14:16 by tpierron          #+#    #+#              #
#    Updated: 2017/11/03 11:10:05 by tpierron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all clean fclean re

LIBNAME = TwoDDL.so

CC = clang++
SRC =	TwoDDL.cpp \

CFLAGS = -Wall -Wextra -Werror -O3 -std=c++11
OBJ_PATH = ./obj/
OBJ_NAME = $(SRC:.cpp=.o)

SDL = -L/Users/$(LOGNAME)/.brew/lib -lSDL2
SDL_PATH = -I/Users/$(LOGNAME)/.brew/include/SDL2

SDLTTF = -L/Users/$(LOGNAME)/.brew/lib -lSDL2_ttf
SDLTTF_PATH = -I/Users/$(LOGNAME)/.brew/include/SDL2_ttf

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(LIBNAME)
$(OBJ_PATH)%.o: %.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) -o $@ -c $(SDL_PATH) $(SDLTTF_PATH) $< -std=c++11

$(LIBNAME): $(OBJ)
	$(CC) -shared -fPIC $(SDL) $(SDLTTF) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(LIBNAME)

re: fclean all
