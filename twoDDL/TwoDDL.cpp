/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TwoDDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:20:23 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/31 11:53:02 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "TwoDDL.hpp"

TwoDDL::TwoDDL(int mapSizeX, int mapSizeY) :
	mapSizeX(mapSizeX), mapSizeY(mapSizeY) {
        
		initSDL();
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
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
    
    for (unsigned int i = 0; i < rectangles.size(); i++) {
        SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
        SDL_RenderFillRect( renderer, &rectangles[i] );
    }
    
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderPresent(renderer);
    // SDL_Flip(win);
}

void    TwoDDL::updateRectangles() {
    if (rectangles.size() != 1)
        createRectangle(50, 50);
}

void    TwoDDL::createRectangle(float x, float y) {
    std::cout << "Q" << std::endl;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 10;
    r.h = 10;
    rectangles.push_back(r);
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

TwoDDL	*initContext(int mapSizeX, int mapSizeY) {
	return new TwoDDL(mapSizeX, mapSizeY);
}

void		destroyContext(TwoDDL *instance) {
	delete instance;
}