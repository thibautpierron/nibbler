/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TwoDDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibautpierron <thibautpierron@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:20:46 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/01 19:13:58 by thibautpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TWODDL_HPP
# define TWODDL_HPP

# include "../shared/IgraphLib.hpp"

# include <iostream>
# include <vector>
# include <deque>

# include <SDL2/SDL.h>

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
		
		std::vector<SDL_Rect>		snakeRect;
		std::vector<SDL_Rect>		foodRect;
		std::vector<SDL_Rect>		sceneryRect;
};

extern "C" {
	TwoDDL	*initContext(int, int);
	void		destroyContext(TwoDDL *);
}

#endif