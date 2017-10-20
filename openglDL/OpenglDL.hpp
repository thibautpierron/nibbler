/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenglDL.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:18:30 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/20 11:29:37 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLDL_HPP
# define OPENGLDL_HPP

# include "../shared/IgraphLib.hpp"
# include "./Shader.class.hpp"
# include "./model/Model.class.hpp"


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
		void	initScenery();

		void	drawBody();
		void	drawHead();
		void	drawFood();
		void	drawScenery();

		void	setCamera();
		float	findHeadOrientation() const;

		int	mapSizeX;
		int mapSizeY;

		std::vector<Vec2> food;
		std::vector<Vec2> snake;
		std::vector<Vec2> scenery;

		SDL_Event		events;
		SDL_GLContext	ctx;
		SDL_Window		*win;

		Shader			*shader;
		GLuint			vao;
		GLuint			vbo;
		Model			*headModel;
		Model			*bodyModel;
		Model			*foodModel;
		Model			*sceneryModel;
};

extern "C" {
	OpenglDL	*initContext(int, int);
	void		destroyContext(OpenglDL *);
}

#endif