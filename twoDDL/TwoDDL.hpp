/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TwoDDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:20:46 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/07 14:33:36 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TWODDL_HPP
# define TWODDL_HPP

# include "../shared/IgraphLib.hpp"

# include <iostream>
# include <vector>
# include <deque>

# include <SDL.h>
# include <SDL_ttf.h>

# define WINDOW_SIZE_X	1024
# define WINDOW_SIZE_Y	1024
# define SQUARE_SIZE	15

class TwoDDL : public IgraphLib {
	public:
		TwoDDL(int, int);
		virtual ~TwoDDL();
		TwoDDL(TwoDDL const & src);
		TwoDDL & operator=(TwoDDL const & rhs);

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
		void	initGameOverStr();

		int	mapSizeX;
		int mapSizeY;

		std::vector<Vec2> food;
		std::deque<Vec2> snake;
		
		SDL_Event		events;
		SDL_Window		*win;
		SDL_Renderer	*renderer;

		TTF_Font		*font;
		SDL_Surface		*gameOverStr;
		SDL_Texture		*fontText;
		SDL_Rect		fontRect;
		
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