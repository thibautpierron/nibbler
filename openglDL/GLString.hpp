/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLString.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 09:56:37 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/06 10:01:17 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLSTRING_H
# define GLSTRING_H

# include <map>
# include "Shader.class.hpp"
# include <gtc/matrix_transform.hpp>
# include <OpenGL/gl3.h>
# include <ft2build.h>
# include FT_FREETYPE_H

struct Character {
    GLuint     textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint     advance;
};

class GLString {
	public:
		GLString();
		~GLString();
		void		render();
		void		renderText(std::string str, float x, float y, glm::vec3 color) const;

	private:
		void		initFont(std::string fontPath);
		void		setupGl();

		Shader		*shader;
		static std::map<GLchar, Character> characters;
		GLuint		VAO;
		GLuint		VBO;
		
};

#endif

