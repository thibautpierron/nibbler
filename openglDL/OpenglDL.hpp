/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenglDL.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:18:30 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/19 14:10:56 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLDL_HPP
# define OPENGLDL_HPP

# include "../shared/IgraphLib.hpp"

# include <iostream>
# include <vector>

# include <OpenGL/gl3.h>
# include <SDL2/SDL.h>

class OpenglDL : public IgraphLib {
	public:
		OpenglDL(int, int);
		virtual ~OpenglDL();

		void					display(std::vector<Vec2> food, std::vector<Vec2> snake);
		virtual Action::Enum	eventManager();

	private:
		OpenglDL();
		void	initSDL();
		void	initGL();

		int	mapSizeX;
		int mapSizeY;

		SDL_Event		events;
		SDL_GLContext	ctx;
		SDL_Window		*win;
};

extern "C" {
	OpenglDL	*initContext(int, int);
	void		destroyContext(OpenglDL *);
}

#endif