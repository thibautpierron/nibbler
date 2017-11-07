/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenglDL.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:18:30 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/07 14:44:14 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLDL_HPP
# define OPENGLDL_HPP

# include "../shared/IgraphLib.hpp"
# include "Shader.class.hpp"
# include "Model.class.hpp"
# include "GLString.hpp"
# include "Skybox.hpp"


# include <iostream>
# include <vector>
# include <deque>

# include <OpenGL/gl3.h>
# include <SDL.h>

# define WINDOW_SIZE_X	1024
# define WINDOW_SIZE_Y	1024

class OpenglDL : public IgraphLib {
	public:
		OpenglDL(int, int);
		virtual ~OpenglDL();
		OpenglDL(OpenglDL const & src);
		OpenglDL & operator=(OpenglDL const &);

		void					display(std::vector<Vec2> food, std::deque<Vec2> snake, bool gameOver);
		virtual Action::Enum	eventManager();
		const char				*toString();

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
		float   findBodyOrientation(unsigned int, unsigned int) const;

		int	mapSizeX;
		int mapSizeY;

		std::vector<Vec2> food;
		std::deque<Vec2> snake;
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
		Skybox			*skybox;
		GLString		*glString;

		bool			gameOver;
};

extern "C" {
	OpenglDL	*initContext(int, int);
	void		destroyContext(OpenglDL *);
}

#endif