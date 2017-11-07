# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2017/11/07 11:41:14 by tpierron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	Nibbler

SRC =	Game.cpp\
		frameTimer.class.cpp\
		main.cpp

INCLUDES =	Game.hpp\
			frameTimer.class.hpp\
			nibbler.hpp

OBJ =	$(SRC:.cpp=.o)

LIB1PATH = openglDL/
LIB2PATH = nCursesDL/
LIB3PATH = twoDDL/

C++ =	g++ -Wall -Wextra -Werror -O3 -std=c++11

%.o:		%.cpp
	@echo "\033[1;32;m[$<]\033[0m : " | tr -d '\n'
	$(C++) -c $<

all:		$(NAME) lib1 lib2 lib3

$(NAME):	$(OBJ) $(INCLUDES)
	$(C++) -o $@ $(OBJ)
	@echo "\033[1;32;m[Compilation Successful]\033[0m"
	@echo "\033[1;36;m$(NAME)\033[1;32;m ready to go !\033[0m"

lib1:
	make -C $(LIB1PATH)
lib2:
	make -C $(LIB2PATH)
lib3:
	make -C $(LIB3PATH)

clean:
	@echo "\033[0;33;m[Clean]\033[0m              : " | tr -d '\n'
	make -C $(LIB1PATH) clean
	make -C $(LIB2PATH) clean
	make -C $(LIB3PATH) clean
	rm -f $(OBJ)

fclean:		clean
	@echo "\033[0;31;m[Deleting $(NAME)]\033[0m : " | tr -d '\n'
	make -C $(LIB1PATH) fclean
	make -C $(LIB2PATH) fclean
	make -C $(LIB3PATH) fclean
	rm -f $(NAME)

re:			fclean all

install:
	./script.sh
	make

.PHONY:		all clean fclean re lib1 lib2 lib3 install
