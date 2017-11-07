/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenglDL.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:18:28 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/07 14:04:16 by tpierron         ###   ########.fr       */
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
        skybox = new Skybox("openglDL/skybox");
        glString = new GLString();
    }

OpenglDL::~OpenglDL() {
    
    delete shader;
    delete headModel;
    delete bodyModel;
    delete foodModel;
    delete sceneryModel;
    delete skybox;
    delete glString;

	SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();

	return;
}

void	OpenglDL::display(std::vector<Vec2> food, std::deque<Vec2> snake, bool gameOver) {
    this->gameOver = gameOver;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (gameOver) {
        this->glString->renderText("GAME OVER",
                                    (WINDOW_SIZE_X - 9 * 48) / 2, (WINDOW_SIZE_Y + 48) / 2,
                                    glm::vec3(0.2f, 0.4f, 1.f));

        SDL_GL_SwapWindow(win);
        return;
    }
    this->food = food;
    this->snake = snake;
    
    setCamera();
    skybox->draw();
    
    drawHead();
    drawBody();
    drawScenery();
    
    drawFood();
    
    // if (gameOver)
    //     this->glString->renderText("GAME OVER",
    //                                 (WINDOW_SIZE_X - 9 * 48) / 2, (WINDOW_SIZE_Y + 48) / 2,
    //                                 glm::vec3(0.2f, 0.4f, 1.f));
    
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
                            WINDOW_SIZE_X, WINDOW_SIZE_Y,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    ctx = SDL_GL_CreateContext(win);
    SDL_RaiseWindow(win);
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
    for(int i = -1; i < mapSizeX; i++) {
        scenery.push_back(Vec2(i, -1));
        scenery.push_back(Vec2(i, mapSizeY));
    }
    for(int i = -1; i < mapSizeY + 1; i++) {
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
                case SDLK_1: return Action::LIB1; break;
                case SDLK_2: return Action::LIB2; break;
                case SDLK_3: return Action::LIB3; break;
                case SDLK_SPACE: return Action::RESTART; break;
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
        transform = glm::translate(transform, glm::vec3(snake[i].x * 2, 0.f, snake[i].y * 2));
        transform = glm::rotate(transform, findBodyOrientation(i, triggerCounter), glm::vec3(0.f, 1.f, 0.f));
        data.push_back(transform);
    }
    shader->use();
    bodyModel->setInstanceBuffer(data);

    bodyModel->draw(shader, snake.size() - 1);
    if (triggerCounter > 40)
        triggerCounter = 0;
    if (!gameOver)
        triggerCounter++;
}

void        OpenglDL::drawScenery() {
    std::vector<glm::mat4> data;
 
    for (unsigned int i = 0; i < scenery.size(); i++) {
        glm::mat4 transform = glm::mat4();
        transform = glm::translate(transform, glm::vec3(scenery[i].x * 2, 0.f, scenery[i].y * 2));
        data.push_back(transform);
    }

    glm::mat4 transform = glm::mat4();
    transform = glm::translate(transform, glm::vec3(mapSizeX, -1.5f, mapSizeY));
    transform = glm::scale(transform, glm::vec3(mapSizeX + 1, 0.5f, mapSizeY + 1));
    data.push_back(transform);

    shader->use();

    sceneryModel->setInstanceBuffer(data);

    sceneryModel->draw(shader, scenery.size() + 1);
}

void        OpenglDL::drawHead() {
    std::vector<glm::mat4> data;
    
    glm::mat4 transform = glm::mat4();
    transform = glm::translate(transform, glm::vec3(snake[0].x * 2, 0.f, snake[0].y * 2));
    transform = glm::rotate(transform, glm::radians(findHeadOrientation()), glm::vec3(0.f, 1.f, 0.f));
    data.push_back(transform);

    shader->use();

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
        return 270.f;
    return 90.f;
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
        transform = glm::translate(transform, glm::vec3(food[i].x * 2, 0.f, food[i].y * 2));
        data.push_back(transform);
    }
    foodModel->setInstanceBuffer(data);
    foodModel->draw(shader, food.size());
}

void        OpenglDL::setCamera() {
    glm::mat4 camera = glm::lookAt(
        glm::vec3(mapSizeX, mapSizeY * 1.5f, mapSizeY * 2 + 10),
        glm::vec3(snake[0].x * 2, 0.f, snake[0].y * 2),
        glm::vec3(0.f, 1.f, 0.f)
    );
    shader->setCamera(camera);
    shader->setView();
}

const char	*OpenglDL::toString()
{
	return ("openglDL/OpenglDL.so");
}

OpenglDL	*initContext(int mapSizeX, int mapSizeY) {
	return new OpenglDL(mapSizeX, mapSizeY);
}

void		destroyContext(OpenglDL *instance) {
	delete instance;
}