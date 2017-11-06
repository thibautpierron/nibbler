# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2017/11/06 11:27:44 by mchevall         ###   ########.fr        #
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
LIBSOUNDPATH = soundDL/

C++ =	g++ -Wall -Wextra -Werror -O3 -std=c++11

%.o:		%.cpp
	@echo "\033[1;32;m[$<]\033[0m : " | tr -d '\n'
	$(C++) -c $<

all:		$(NAME) lib1 lib2 lib3 libsound

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
libsound:
	make -C $(LIBSOUNDPATH)

clean:
	@echo "\033[0;33;m[Clean]\033[0m              : " | tr -d '\n'
	make -C $(LIB1PATH) clean
	make -C $(LIB2PATH) clean
	make -C $(LIB3PATH) clean
	make -C $(LIBSOUNDPATH) clean	
	rm -f $(OBJ)

fclean:		clean
	@echo "\033[0;31;m[Deleting $(NAME)]\033[0m : " | tr -d '\n'
	make -C $(LIB1PATH) fclean
	make -C $(LIB2PATH) fclean
	make -C $(LIB3PATH) fclean
	make -C $(LIBSOUNDPATH) fclean
	rm -f $(NAME)

re:			fclean all

install:
	./script.sh
	make

.PHONY:		all clean fclean re lib1 lib2 lib3 libsound install
