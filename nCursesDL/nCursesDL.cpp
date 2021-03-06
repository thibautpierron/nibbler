/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nCursesDL.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:42:02 by mchevall          #+#    #+#             */
/*   Updated: 2017/11/07 13:54:23 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nCursesDL.hpp"

nCursesDL::nCursesDL(){;}
nCursesDL::nCursesDL(int mapX, int mapY) : _mapX(mapX), _mapY(mapY)
{
	system("osascript termresizing");
	flushinp();
	setup_ncurses();
	this->map = subwin(stdscr, (this->_mapY + 2), 2 * (this->_mapX + 1), 0, 0);
	makeBorder();
}


nCursesDL::nCursesDL( nCursesDL const & src )
{
    *this = src;
    return;
}

nCursesDL::~nCursesDL()
{
	delwin(this->map);
	endwin();
    return;
}

nCursesDL &	nCursesDL::operator=( nCursesDL const & rhs )
{
	if (this != &rhs)
		;
    return *this;
}

void			nCursesDL::display(std::vector<Vec2> food, std::deque<Vec2> snake, bool gameOver)
{
	for (int i = 1; i <= 2 * this->_mapX+2; i++)
	for (int j = 1; j < this->_mapY+2; j++)
		mvwprintw(this->map, j, i,"%c", ' ');
	
	wattron(this->map, COLOR_PAIR(35));
	for (size_t i= 0; i < food.size(); i++)
	mvwprintw(this->map, food[i].y + 1, 2 * (food[i].x)+ 1, "%s", "  ");
	wattroff(this->map, COLOR_PAIR(35));
	
	wattron(this->map, COLOR_PAIR(38));
	for(size_t i = 0; i < snake.size(); i++)
	mvwprintw(this->map, snake[i].y + 1, 2 * snake[i].x + 1, "%s", "  ");
	wattroff(this->map, COLOR_PAIR(38));
	
	wattron(this->map, COLOR_PAIR(37));
	mvwprintw(this->map, snake[0].y + 1, 2 * snake[0].x + 1, "%s", "  ");
	wattroff(this->map, COLOR_PAIR(37));
	
	if (gameOver) {
		int midscreenY = (_mapY + 2) / 2;
		int midscreenX = (_mapX + 2);
		wattron(this->map, COLOR_PAIR(25));
		mvwprintw(this->map, midscreenY - 2, midscreenX - 9/2,"%s", "GAME OVER");
		mvwprintw(this->map, midscreenY , midscreenX - 13/2,"%s", "PRESS \"SPACE\"");
		mvwprintw(this->map, midscreenY + 2, midscreenX - 13/2,"%s", "TO PLAY AGAIN");
		wattroff(this->map, COLOR_PAIR(25));
	}
	this->makeBorder();
}

int					nCursesDL::checkInput() const
{
	int				input;

	input = getch();
	if (input != ERR) {
		ungetch(input);
		return (1);
	}
	else
		return (0);
}

Action::Enum	nCursesDL::eventManager()
{
	int				input;
	
	if (checkInput())
	{
		input = getch();
		{
			switch (input)
			{
				case KEY_LEFT:
					return(Action::LEFT);
				case KEY_RIGHT:
					return(Action::RIGHT);
				case 27:
					return(Action::ESCAPE);
				case 49:
					return(Action::LIB1);
				case 50:
					return(Action::LIB2);
				case 51:
					return(Action::LIB3);
				case 32:
					return(Action::RESTART);
				default:
					return(Action::NONE);
			}
		}
	}
	return (Action::NONE);
}

void			nCursesDL::makeBorder() const
{
	wattron(this->map, COLOR_PAIR(30));
	wborder(this->map, '#', '#', '#', '#', '#', '#', '#', '#');
	wattroff(this->map, COLOR_PAIR(30));
	wnoutrefresh(this->map);
	doupdate();
}

const char		*nCursesDL::toString()
{
	return ("nCursesDL/nCursesDL.so");
}

nCursesDL	*initContext(int mapSizeX, int mapSizeY) {
	return new nCursesDL(mapSizeX, mapSizeY);
}

void		destroyContext(nCursesDL *instance) {
	delete instance;
}
/* Accessors */
