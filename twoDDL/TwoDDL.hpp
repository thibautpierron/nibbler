/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TwoDDL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:20:46 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/31 11:50:39 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TWODDL_HPP
# define TWODDL_HPP

# include "../shared/IgraphLib.hpp"

# include <iostream>
# include <vector>
# include <deque>

# include <SDL.h>

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
		void	createRectangle(float x, float y);
		void	updateRectangles();

		int	mapSizeX;
		int mapSizeY;

		std::vector<Vec2> food;
		std::deque<Vec2> snake;
		std::vector<Vec2> scenery;

		SDL_Event		events;
		SDL_Window		*win;
		SDL_Renderer	*renderer;

		std::vector<SDL_Rect>		rectangles;
};

extern "C" {
	TwoDDL	*initContext(int, int);
	void		destroyContext(TwoDDL *);
}

#endif