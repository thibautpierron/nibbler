# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 14:02:22 by fdexheim          #+#    #+#              #
#    Updated: 2017/10/27 15:29:42 by mchevall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBNAME =	nCursesDL.so

SRC =	nCursesDL.cpp\
		ncursesetup.cpp

INCLUDES =	nCursesDL.hpp\
			ncursesetup.hpp

OBJ =	$(SRC:.cpp=.o)

LIB = -lncurses

C++ =	clang++ -Wall -Wextra -Werror -O3 -std=c++11

%.o:		%.cpp
	@echo "\033[1;32;m[$<]\033[0m : " | tr -d '\n'
	$(C++) -c $<

all:		$(LIBNAME)

$(LIBNAME):	$(OBJ) $(INCLUDES)
	$(C++) -shared -fPIC -o $@ $(OBJ) $(LIB) 
	@echo "\033[1;32;m[Compilation Successful]\033[0m"
	@echo "\033[1;36;m$(LIBNAME)\033[1;32;m ready to go !\033[0m"

clean:
	@echo "\033[0;33;m[Clean]\033[0m              : " | tr -d '\n'
	rm -f $(OBJ)

fclean:		clean
	@echo "\033[0;31;m[Deleting $(LIBNAME)]\033[0m : " | tr -d '\n'
	rm -f $(LIBNAME)

re:			fclean all

.PHONY:		all clean fclean re
