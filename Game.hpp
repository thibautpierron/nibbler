/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:04:49 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/25 16:57:26 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <vector>
# include <deque>
# include <iostream>
# include "frameTimer.class.hpp"
# include "./shared/IgraphLib.hpp"
# include "./shared/constants.hpp"

enum Direction { NORTH , EAST, SOUTH, WEST };

class Game {
	public:
		Game(int, int);
		~Game();

		std::vector<Vec2> 	getFood() const;
		std::deque<Vec2> 	getSnake() const;
		void				compute(Action::Enum action);
		
	private:
		Game();
		void		checkCollisions();
		bool		checkFoodCollision();
		bool		checkWallCollision();
		bool		checkSnakeCollision();
		void		initSnake();
		void		generateFood();
		void		getNextMoveDirection(Action::Enum);
		void		moveSnake();
		
		int		mapSizeX;
		int		mapSizeY;
		
		int		gameSpeed;
		
		frameTimer			*gameFrameTimer;
		std::vector<Vec2>	food;
		std::deque<Vec2>	snake;
		Direction			direction;
		Action::Enum		action;
		bool				foodContactFlag;
};

#endif