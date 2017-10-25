/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenglDL.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:18:28 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/25 16:16:57 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenglDL.hpp"

OpenglDL::OpenglDL(int mapSizeX, int mapSizeY) :
	mapSizeX(mapSizeX), mapSizeY(mapSizeY) {
        
		initSDL();
        initGL();
        initScenery();
        
        shader = new Shader("./openglDL/shaders/static_model_instanced.glvs",
                            "./openglDL/shaders/simple_diffuse.glfs");

        headModel = new Model("./openglDL/head.obj", false);
        bodyModel = new Model("./openglDL/body.obj", false);
        foodModel = new Model("./openglDL/food.obj", false);
        sceneryModel = new Model("./openglDL/wall.obj", false);
}

OpenglDL::~OpenglDL() {
    
    delete shader;
    delete headModel;
    delete bodyModel;
    delete foodModel;
    delete sceneryModel;

	SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();

	return;
}

void	OpenglDL::display(std::vector<Vec2> food, std::deque<Vec2> snake) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->food = food;
    this->snake = snake;

    setCamera();
    
    shader->use();

    drawHead();
    drawBody();
    drawFood();
    drawScenery();

	SDL_GL_SwapWindow(win);
}

void	OpenglDL::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    win = SDL_CreateWindow("Nibbler",
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
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void    OpenglDL::initScenery() {
    for(int i = 0; i < mapSizeX; i++) {
        scenery.push_back(Vec2(i, -1));
        scenery.push_back(Vec2(i, mapSizeY));
    }
    for(int i = 0; i < mapSizeY; i++) {
        scenery.push_back(Vec2(-1, i));
        scenery.push_back(Vec2(mapSizeX, i));
    }
}

Action::Enum    OpenglDL::eventManager() {
    static int repeatFlag = 0;
    while (SDL_PollEvent(&events)) {
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
    }
	return Action::NONE;
}

void        OpenglDL::drawBody() {
    static unsigned int triggerCounter = 0;
    std::vector<glm::mat4> data;
 
    for (unsigned int i = 1; i < snake.size(); i++) {
        glm::mat4 transform = glm::mat4();
        transform = glm::translate(transform, glm::vec3(snake[i].x * 2, snake[i].y * 2, 0.f));
        transform = glm::rotate(transform, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
        transform = glm::rotate(transform, findBodyOrientation(i, triggerCounter), glm::vec3(0.f, 1.f, 0.f));
        data.push_back(transform);
    }
    bodyModel->setInstanceBuffer(data);

    bodyModel->draw(shader, snake.size() - 1);
    if (triggerCounter > 40)
        triggerCounter = 0;
    triggerCounter++;
}

void        OpenglDL::drawScenery() {
    std::vector<glm::mat4> data;
 
    for (unsigned int i = 0; i < scenery.size(); i++) {
        glm::mat4 transform = glm::mat4();
        transform = glm::translate(transform, glm::vec3(scenery[i].x * 2, scenery[i].y * 2, 0.f));
        data.push_back(transform);
    }
    sceneryModel->setInstanceBuffer(data);

    sceneryModel->draw(shader, scenery.size());
}

void        OpenglDL::drawHead() {
    std::vector<glm::mat4> data;
    
    glm::mat4 transform = glm::mat4();
    transform = glm::translate(transform, glm::vec3(snake[0].x * 2, snake[0].y * 2, 0.f));
    transform = glm::rotate(transform, glm::radians(findHeadOrientation()), glm::vec3(0.f, 0.f, 1.f));
    data.push_back(transform);
    headModel->setInstanceBuffer(data);
    
    headModel->draw(shader, 1);
}

float       OpenglDL::findHeadOrientation() const {
    int diffX = snake[0].x - snake[1].x;
    int diffY = snake[0].y - snake[1].y;
    if (diffX > 0)
        return 0.f;
    else if (diffX < 0)
        return 180.f;
    else if (diffY > 0)
        return 90.f;
    return 270.f;
}

float       OpenglDL::findBodyOrientation(unsigned int index, unsigned int trigger) const {
    int offset = index % 2 ? 20.f : -20.f;
    int sign = 1;
    if(trigger > 20)
        sign = -1;
    return offset * sign;
}

void        OpenglDL::drawFood() {
    std::vector<glm::mat4> data;
    
    for (unsigned int i = 0; i < food.size(); i++) {
        glm::mat4 transform = glm::mat4();
        transform = glm::translate(transform, glm::vec3(food[i].x * 2, food[i].y * 2, 0.f));
        data.push_back(transform);
    }
    foodModel->setInstanceBuffer(data);
    foodModel->draw(shader, food.size());
}

void        OpenglDL::setCamera() {
    glm::mat4 camera = glm::lookAt(
        glm::vec3(mapSizeX, - mapSizeY / 2, mapSizeY),
        glm::vec3(snake[0].x * 2, snake[0].y * 2, 0.f),
        glm::vec3(0.f, 0.f, 1.f)
    );
    shader->setCamera(camera);
    shader->setView();
}

OpenglDL	*initContext(int mapSizeX, int mapSizeY) {
	return new OpenglDL(mapSizeX, mapSizeY);
}

void		destroyContext(OpenglDL *instance) {
	delete instance;
}