/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:09:46 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/25 16:53:29 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game(int mapSizeX, int mapSizeY) : mapSizeX(mapSizeX), mapSizeY(mapSizeY){
	initSnake();
	generateFood();
	generateFood();

	gameFrameTimer = new frameTimer(60.0f);
	gameSpeed = 4;
	direction = NORTH;
	action = Action::NONE;
	foodContactFlag = false;
}

Game::~Game() {};
 
void    Game::initSnake() {
    snake.push_back(Vec2(mapSizeX / 2, mapSizeY / 2));
    snake.push_back(Vec2(mapSizeX / 2, (mapSizeY / 2) - 1));
    snake.push_back(Vec2(mapSizeX / 2, (mapSizeY / 2) - 2));
    snake.push_back(Vec2(mapSizeX / 2, (mapSizeY / 2) - 3));
}

void    Game::generateFood() {
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
	{
		if(action == Action::LEFT || action == Action::RIGHT)
			this->action = action;
		gameFrameTimer->updateTimeBeginningLoop();
		if (gameFrameTimer->frameNumber % gameSpeed == 0)
		{
			getNextMoveDirection(this->action);
			moveSnake();
			checkCollisions();
			this->action = Action::NONE;
		}
		gameFrameTimer->updateTimeEndLoop();
		}
	
}

void	Game::checkCollisions() {
	if (checkWallCollision())
		std::cout << "WALL COLLISION" << std::endl;
	if (checkSnakeCollision())
		std::cout << "SNAKE COLLISION" << std::endl;
	if (checkFoodCollision()) {
		foodContactFlag = true;
		generateFood();
	}
}

bool		Game::checkFoodCollision() {
	for (unsigned int i = 0; i < food.size(); i++) {
		if (snake[0].x == food[i].x && snake[0].y == food[i].y) {
			food.erase(food.begin() + i);
			return ((static_cast<int>(snake.size()) < mapSizeX * mapSizeY) ? true : false);
		}
	}
	return false;
}

bool		Game::checkWallCollision() {
	if (snake[0].x < 0 || snake[0].x >= mapSizeX || 
		snake[0].y < 0 || snake[0].y >= mapSizeY)
		return true;
	return false;
}

bool		Game::checkSnakeCollision() {
	for (unsigned int i = 1; i < snake.size(); i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return true;
	}
	return false;
}


void	Game::getNextMoveDirection(Action::Enum action) {
	if(action == Action::LEFT)
		direction =  static_cast<Direction>((direction - 1) % 4);
	else if(action == Action::RIGHT)
		direction =  static_cast<Direction>((direction + 1) % 4);

	if (direction < 0)
		direction = WEST;
}

void		Game::moveSnake() {
	int nextHeadX= snake[0].x;
	int nextHeadY= snake[0].y;
	switch (direction) {
		case NORTH: nextHeadY++; break;
		case SOUTH: nextHeadY--; break;
		case EAST: nextHeadX++; break;
		case WEST: nextHeadX--; break;
	}
	snake.push_front(Vec2(nextHeadX, nextHeadY));
	if (!foodContactFlag)
		snake.pop_back();
	else
		foodContactFlag = false;
}

std::vector<Vec2> 		Game::getFood() const {
	return food;
}

std::deque<Vec2> 		Game::getSnake() const {
	return snake;
}
