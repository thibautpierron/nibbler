/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:09:46 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/20 13:34:04 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game(int mapSizeX, int mapSizeY) : mapSizeX(mapSizeX), mapSizeY(mapSizeY){
	initSnake();
	initFood();

	gameSpeed = 6.f / 60.f;
    gameTick = 0.f;
}

Game::~Game() {};
 
void    Game::initSnake() {
    snake.push_back(Vec2(3, 3));
    snake.push_back(Vec2(3, 4));
    snake.push_back(Vec2(3, 5));
    snake.push_back(Vec2(3, 6));
}

void    Game::initFood() {
	int nX = snake[0].x;
	int nY = snake[0].y;
	bool flag = true;

	while (flag) {
		flag = false;
		nX = rand() % mapSizeX;
		nY = rand() % mapSizeY;
		for (unsigned int i = 0; i < snake.size(); i++) {
			if (nX == snake[i].x && nY == snake[i].y)
				flag = true;
		}
	}

    food.push_back(Vec2(nX, nY));
}

void	Game::compute(Action::Enum action) {
	if (action)
		action = Action::NONE;
}

bool	Game::checkCollision() {
	return false;
}

std::vector<Vec2> 		Game::getFood() const {
	return food;
}

std::vector<Vec2> 		Game::getSnake() const {
	return snake;
}
