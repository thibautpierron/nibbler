# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2017/10/30 18:06:19 by mchevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

LIBNAME = soundDL.so

CC = clang++
SRC =	soundDL.cpp 

CFLAGS = -Wall -Wextra -Werror -std=c++11
OBJ_PATH = ./obj/
OBJ_NAME = $(SRC:.cpp=.o)

SDL = -L/Users/$(LOGNAME)/.brew/lib -lSDL2_Mixer
SDL2 = -L/Users/$(LOGNAME)/.brew/lib -lSDL2
SDL_PATH = -I/Users/$(LOGNAME)/.brew/include/SDL2

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(LIBNAME)
$(OBJ_PATH)%.o: %.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) -o $@ -c $(SDL_PATH) $< -std=c++11

$(LIBNAME): $(OBJ)
	$(CC) -shared -fPIC $(SDL) $(SDL2) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(LIBNAME)

re: fclean all
