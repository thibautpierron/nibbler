/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TwoDDL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:20:23 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/06 14:26:46 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "TwoDDL.hpp"

TwoDDL::TwoDDL(int mapSizeX, int mapSizeY) :
	mapSizeX(mapSizeX), mapSizeY(mapSizeY) {
        
    initSDL();
    setOffset();
    initScenery();
    initGameOverStr();

    createRectangle(foodRect);
    createRectangle(foodRect);
}

void    TwoDDL::initGameOverStr() {
    TTF_Init();

    font = TTF_OpenFont("twoDDL/oasis.TTF", 50);
    
    SDL_Color color = {0, 0, 0, 0};
    gameOverStr = TTF_RenderText_Solid(font, "GAME OVER", color);
    
    fontText = SDL_CreateTextureFromSurface(renderer, gameOverStr);
    
    fontRect.x = (WINDOW_SIZE_X - 250) / 2;
    fontRect.y = (WINDOW_SIZE_Y - 100) / 2;
    fontRect.w = 250;
    fontRect.h = 100;
}

TwoDDL::~TwoDDL() {

    // for (unsigned int i = 0; i < rectangles.size(); i++) {
    //     SDL_FreeSurface(rectangles[i]);
    // }

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_FreeSurface(gameOverStr);
    SDL_DestroyTexture(fontText);
    SDL_Quit();

    SDL_Quit();

	return;
}

void	TwoDDL::display(std::vector<Vec2> food, std::deque<Vec2> snake, bool gameOver) {
    if (gameOver) {
        SDL_RenderCopy(renderer, fontText, NULL, &fontRect);
        SDL_RenderPresent(renderer);
        return;
    }

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
    if (snakeRect.size() > snake.size())
        snakeRect.clear();

    for (unsigned int i = 0; snakeRect.size() != snake.size(); i++) {
        createRectangle(snakeRect);
    }

    for (unsigned int i = 0; i < snake.size(); i++) {
        snakeRect[i].x = snake[i].x * SQUARE_SIZE + SQUARE_SIZE + offsetX;
        snakeRect[i].y = snake[i].y * SQUARE_SIZE + SQUARE_SIZE + offsetY;
    }

    for (unsigned int i = 0; i < food.size(); i++) {
        foodRect[i].x = food[i].x * SQUARE_SIZE + SQUARE_SIZE + offsetX;
        foodRect[i].y = food[i].y * SQUARE_SIZE + SQUARE_SIZE + offsetY;
    }
}

void    TwoDDL::initScenery() {
    for(int i = 0; i <= mapSizeX; i++) {
        createRectangle(sceneryRect);
        sceneryRect.back().x = i * SQUARE_SIZE + offsetX;
        sceneryRect.back().y = offsetY;
        createRectangle(sceneryRect);
        sceneryRect.back().x = i * SQUARE_SIZE + offsetX;
        sceneryRect.back().y = mapSizeY * SQUARE_SIZE + SQUARE_SIZE + offsetY;
    }
    for(int i = 0; i <= mapSizeY + 1; i++) {
        createRectangle(sceneryRect);
        sceneryRect.back().x = offsetX;
        sceneryRect.back().y = i * SQUARE_SIZE + offsetY;
        createRectangle(sceneryRect);
        sceneryRect.back().y = i * SQUARE_SIZE + offsetY;
        sceneryRect.back().x = mapSizeX * SQUARE_SIZE + SQUARE_SIZE + offsetX;
    }
}

void    TwoDDL::setOffset() {
    offsetX = (WINDOW_SIZE_X - mapSizeX * SQUARE_SIZE) / 2;
    offsetY = (WINDOW_SIZE_Y - mapSizeY * SQUARE_SIZE) / 2;
}

void    TwoDDL::createRectangle(std::vector<SDL_Rect> & list) {
    SDL_Rect r;
    
    r.x = 0;
    r.y = 0;
    r.w = SQUARE_SIZE;
    r.h = SQUARE_SIZE;
    list.push_back(r);
}

void	TwoDDL::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Nibbler",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_SIZE_X, WINDOW_SIZE_Y,
                            SDL_WINDOW_SHOWN);

    SDL_RaiseWindow(win);
    renderer =  SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize( renderer, WINDOW_SIZE_X, WINDOW_SIZE_Y );
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
	return ("twoDDL/TwoDDL.so");
}

TwoDDL	    *initContext(int mapSizeX, int mapSizeY) {
	return new TwoDDL(mapSizeX, mapSizeY);
}

void		destroyContext(TwoDDL *instance) {
	delete instance;
}