/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:09:46 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/30 13:55:43 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game(int mapSizeX, int mapSizeY, const char *libnames[3]) : lib1(libnames[0]), lib2(libnames[1]), lib3(libnames[2]), mapSizeX(mapSizeX), mapSizeY(mapSizeY){
	initLib(lib1);
	initSnake();
	generateFood();
	generateFood();
	
	gameFrameTimer = new frameTimer(60.0f);
	gameSpeed = 4;
	direction = NORTH;
	action = Action::NONE;
	foodContactFlag = false;
	gameOver = false;
}

Game::~Game() {
	destroyContext(currentlib);
	dlclose(dlHandle);
}

void	Game::restart() {
	snake.clear();
	direction = NORTH;
	initSnake();
	food.clear();
	generateFood();
	generateFood();
	gameOver = false;
	action = Action::NONE;
}

void	Game::initLib(const char *lib)
{
	this->dlHandle = dlopen(lib, RTLD_LAZY | RTLD_LOCAL);
	
	this->initContext = (IgraphLib *(*)(int, int))dlsym(dlHandle, "initContext");
	checkDlError(dlHandle);
	this->destroyContext = (void(*)(IgraphLib *))dlsym(dlHandle, "destroyContext");
	checkDlError(dlHandle);
	currentlib = initContext(mapSizeX,mapSizeY);
}

void	Game::initSnake() {
    snake.push_back(Vec2(mapSizeX / 2, mapSizeY / 2));
    snake.push_back(Vec2(mapSizeX / 2, (mapSizeY / 2) - 1));
    snake.push_back(Vec2(mapSizeX / 2, (mapSizeY / 2) - 2));
    snake.push_back(Vec2(mapSizeX / 2, (mapSizeY / 2) - 3));
}

void	Game::checkDlError(void *dlHandle) {
    if (!dlHandle) {
        std::cerr << "error: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void	Game::generateFood() {
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

Action::Enum	Game::eventManager()
{
	return (currentlib->eventManager());
}

void	Game::compute(Action::Enum action) {
	if(action == Action::LEFT || action == Action::RIGHT || action == Action::LIB1|| action == Action::LIB2|| action == Action::LIB3)
		this->action = action;
	if(gameOver && action == Action::RESTART)
		restart();
	gameFrameTimer->updateTimeBeginningLoop();
	if (gameFrameTimer->frameNumber % gameSpeed == 0)
	{
		getNextMoveDirection(this->action);
		catchLibChange(this->action);
		if(!gameOver) {
			moveSnake();
			gameOver = checkCollisions();
		}
		this->action = Action::NONE;
	}
	gameFrameTimer->updateTimeEndLoop();
}

void	Game::display()
{
	currentlib->display(food, snake, gameOver);
}



bool	Game::checkCollisions() {
	if (checkWallCollision())
		return true;
	if (checkSnakeCollision())
		return true;
	if (checkFoodCollision()) {
		foodContactFlag = true;
		generateFood();
	}
	return false;
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

void	Game::catchLibChange(Action::Enum action)
{
	if (action == Action::LIB1 && std::strcmp(currentlib->toString(), lib1))
	{
		destroyContext(currentlib);
		initLib(lib1);
		usleep(1500000);
	}
	else if (action == Action::LIB2 && std::strcmp(currentlib->toString(), lib2))
	{
		destroyContext(currentlib);
		initLib(lib2);
		usleep(1500000);
		
	}
	else if (action == Action::LIB3 && std::strcmp(currentlib->toString(), lib3))
	{
		destroyContext(currentlib);
		initLib(lib3);
		usleep(1500000);
	}
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
	int nextHeadX = snake[0].x;
	int nextHeadY = snake[0].y;
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
