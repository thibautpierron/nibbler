/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TwoDDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:20:46 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/03 10:36:02 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TWODDL_HPP
# define TWODDL_HPP

# include "../shared/IgraphLib.hpp"

# include <iostream>
# include <vector>
# include <deque>

# include <SDL.h>

# define WINDOW_SIZE_X	1024
# define WINDOW_SIZE_Y	1024
# define SQUARE_SIZE	15

class TwoDDL : public IgraphLib {
	public:
		TwoDDL(int, int);
		virtual ~TwoDDL();

		void					display(std::vector<Vec2> food, std::deque<Vec2> snake, bool gameOver);
		virtual Action::Enum	eventManager();
		const char				*toString();

	private:
		TwoDDL();
		void	initSDL();
		void	setOffset();
		void	initScenery();
		void	createRectangle(std::vector<SDL_Rect> &);
		void	updateRectangles();

		int	mapSizeX;
		int mapSizeY;

		std::vector<Vec2> food;
		std::deque<Vec2> snake;
		
		SDL_Event		events;
		SDL_Window		*win;
		SDL_Renderer	*renderer;
		
		unsigned int	offsetX;
		unsigned int	offsetY;

		std::vector<SDL_Rect>		snakeRect;
		std::vector<SDL_Rect>		foodRect;
		std::vector<SDL_Rect>		sceneryRect;
};

extern "C" {
	TwoDDL	*initContext(int, int);
	void		destroyContext(TwoDDL *);
}

#endif