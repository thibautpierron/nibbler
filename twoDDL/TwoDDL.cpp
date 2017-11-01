/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TwoDDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibautpierron <thibautpierron@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:20:23 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/01 19:23:10 by thibautpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "TwoDDL.hpp"

TwoDDL::TwoDDL(int mapSizeX, int mapSizeY) :
	mapSizeX(mapSizeX), mapSizeY(mapSizeY) {
        
        initSDL();
        initScenery();
    }

TwoDDL::~TwoDDL() {

    // for (unsigned int i = 0; i < rectangles.size(); i++) {
    //     SDL_FreeSurface(rectangles[i]);
    // }
    SDL_Quit();

	return;
}

void	TwoDDL::display(std::vector<Vec2> food, std::deque<Vec2> snake, bool gameOver) {
    if (gameOver)
        return;

    this->food = food;
    this->snake = snake;

    updateRectangles();

    SDL_RenderClear( renderer );
    SDL_SetRenderDrawColor( renderer, 150, 150, 150, 255 );
    
    for (unsigned int i = 0; i < snakeRect.size(); i++) {
        SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
        SDL_RenderFillRect( renderer, &snakeRect[i] );
    }

    for (unsigned int i = 0; i < foodRect.size(); i++) {
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
        SDL_RenderFillRect( renderer, &foodRect[i] );
    }

    for (unsigned int i = 0; i < sceneryRect.size(); i++) {
        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
        SDL_RenderFillRect( renderer, &sceneryRect[i] );
    }
    
    SDL_SetRenderDrawColor( renderer, 150, 150, 150, 255 );
    SDL_RenderPresent(renderer);
}

void    TwoDDL::updateRectangles() {
    while (snakeRect.size() != snake.size()) {
        createRectangle(snakeRect);
    }
    for (unsigned int i = 0; i < snake.size(); i++) {
        snakeRect[i].x = snake[i].x * 10;
        snakeRect[i].y = snake[i].y * 10;
    }

    while (foodRect.size() != snake.size()) {
        createRectangle(foodRect);
    }
    for (unsigned int i = 0; i < food.size(); i++) {
        foodRect[i].x = food[i].x * 10;
        foodRect[i].y = food[i].y * 10;
    }
}

void    TwoDDL::initScenery() {
    for(int i = 0; i < mapSizeX; i += 2) {
        createRectangle(sceneryRect);
        sceneryRect[i].x = i * 10;
        createRectangle(sceneryRect);
        sceneryRect[i + 1].x = i * 10;
        sceneryRect[i + 1].y = mapSizeY * 10;
    }
}

void    TwoDDL::createRectangle(std::vector<SDL_Rect> & list) {
    SDL_Rect r;
    
    r.x = 0;
    r.y = 0;
    r.w = 10;
    r.h = 10;
    list.push_back(r);
}

void	TwoDDL::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Nibbler",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            1024, 1024,
                            SDL_WINDOW_SHOWN);

    renderer =  SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize( renderer, 1024, 1024 );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

}

Action::Enum    TwoDDL::eventManager() {
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

const char	*TwoDDL::toString()
{
	return ("TwoDDL/TwoDDL.so");
}

TwoDDL	    *initContext(int mapSizeX, int mapSizeY) {
	return new TwoDDL(mapSizeX, mapSizeY);
}

void		destroyContext(TwoDDL *instance) {
	delete instance;
}