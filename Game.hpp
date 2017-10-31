/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:04:49 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/31 16:10:17 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <vector>
# include <deque>
# include <iostream>
# include <dlfcn.h>
# include "shared/IgraphLib.hpp"
# include "frameTimer.class.hpp"
# include "./shared/IsoundLib.hpp"
# include "./shared/IgraphLib.hpp"
# include "./shared/constants.hpp"

enum Direction { NORTH , EAST, SOUTH, WEST };

class Game {
	public:
		Game(int, int, const char *tab[3]);
		~Game();

		std::vector<Vec2> 	getFood() const;
		std::deque<Vec2> 	getSnake() const;
		Action::Enum		eventManager();
		void				compute(Action::Enum action);
		void				display();
		
		
	private:
		Game();
		
		void		checkDlError(void *dlHandle);
		bool		checkCollisions();
		bool		checkFoodCollision();
		bool		checkWallCollision();
		bool		checkSnakeCollision();
		void		initLib(const char *lib);
		void		initSnake();
		void		generateFood();
		void		getNextMoveDirection(Action::Enum);
		void		catchLibChange(Action::Enum);
		void		moveSnake();
		void		restart();
		
		void		*dlHandle;
		IgraphLib	*(*initContext)(int, int);
		void		(*destroyContext)(IgraphLib *);
		
		void			*dlHandleSound;
		IsoundLib		*(*initContextSound)(bool);
		void			(*destroyContextSound)(IsoundLib *);
		

		IgraphLib	*currentlib;
		const char	*lib1;
		const char	*lib2;
		const char	*lib3;

		void			initLibSound(const char *lib);
		IsoundLib		*currentlibsound;
		const char		*libsound1;
		
		int			mapSizeX;
		int			mapSizeY;

		int			gameSpeed;
		int			volume;

		frameTimer			*gameFrameTimer;
		std::vector<Vec2>	food;
		std::deque<Vec2>	snake;
		Direction			direction;
		Action::Enum		action;
		bool				foodContactFlag;
		bool				gameOver;
};

#endif