/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenglDL.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:18:28 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/19 17:52:42 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenglDL.hpp"

OpenglDL::OpenglDL(int mapSizeX, int mapSizeY) :
	mapSizeX(mapSizeX), mapSizeY(mapSizeY) {
        
		initSDL();
        initGL();
        
        shader = new Shader("./openglDL/shaders/static_model_instanced.glvs",
                            "./openglDL/shaders/simple_diffuse.glfs");

        model = new Model("./openglDL/body.obj", false);
        
}

OpenglDL::~OpenglDL() {
	SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
	return;
}

void	OpenglDL::display(std::vector<Vec2> food, std::vector<Vec2> snake) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Vec2 v(0,0);
	food.push_back(v);
    snake.push_back(v);

    // shader->use();
	
    // glm::mat4 camera = glm::lookAt(
    //     glm::vec3(0.f, -4.f, 5.f),
    //     glm::vec3(0.f, 0.f, 0.f),
    //     glm::vec3(0.f, 0.f, 1.f)
    // );
    // shader->setCamera(camera);
    // shader->setView();

    // std::vector<glm::mat4> data;
    // glm::mat4 transform = glm::mat4();
    // transform = glm::translate(transform, glm::vec3(snake[0].x + 0.5f, snake[0].y + 0.5f, 0.f));
    // data.push_back(transform);
    // model->setInstanceBuffer(data);

    // model->draw(shader, snake.size());

	SDL_GL_SwapWindow(win);
}

void	OpenglDL::initSDL() {
    std::cout << "initSDL" << std::endl;
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_Window *win = SDL_CreateWindow("Nibbler",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        1024, 1024,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    ctx = SDL_GL_CreateContext(win);
    if(ctx == 0) {
        std::cout << SDL_GetError() << std::endl;
        exit(0);
    }
}

void	OpenglDL::initGL() {
    std::cout << "initGL" << std::endl;
    glClearColor(0.5f, 1.5f, 0.5f, 0.5f);
    
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

Action::Enum    OpenglDL::eventManager() {
    static int repeatFlag = 0;
    SDL_PollEvent(&events);
    if (events.window.event == SDL_WINDOWEVENT_CLOSE || events.key.keysym.sym == SDLK_ESCAPE) {
        return Action::ESCAPE;
    }
    if (events.type == SDL_KEYUP)
    repeatFlag = 0;
    if (events.type == SDL_KEYDOWN && repeatFlag == 0) {
        repeatFlag = 1;
        switch(events.key.keysym.sym) {
            case SDLK_RIGHT: return Action::RIGHT; break;
            case SDLK_LEFT: return Action::LEFT; break;
        }
	}
	return Action::NONE;
}

OpenglDL	*initContext(int mapSizeX, int mapSizeY) {
	return new OpenglDL(mapSizeX, mapSizeY);
}

void		destroyContext(OpenglDL *instance) {
	delete instance;
}