# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2017/10/27 15:32:25 by mchevall         ###   ########.fr        #
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
#LIB3PATH = openglDL/

C++ =	g++ -Wall -Wextra -Werror -O3 -std=c++11

%.o:		%.cpp
	@echo "\033[1;32;m[$<]\033[0m : " | tr -d '\n'
	$(C++) -c $<

all:		$(NAME)

$(NAME):	$(OBJ) $(INCLUDES)
	$(C++) -o $@ $(OBJ)
	make -C $(LIB1PATH)
	make -C $(LIB2PATH)
	@echo "\033[1;32;m[Compilation Successful]\033[0m"
	@echo "\033[1;36;m$(NAME)\033[1;32;m ready to go !\033[0m"

clean:
	@echo "\033[0;33;m[Clean]\033[0m              : " | tr -d '\n'
	make -C $(LIB1PATH) clean
	make -C $(LIB2PATH) clean
	rm -f $(OBJ)

fclean:		clean
	@echo "\033[0;31;m[Deleting $(NAME)]\033[0m : " | tr -d '\n'
	make -C $(LIB1PATH) fclean
	make -C $(LIB2PATH) fclean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
