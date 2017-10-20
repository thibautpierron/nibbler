/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:04:49 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/20 13:33:46 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <vector>
# include <iostream>
# include "./shared/IgraphLib.hpp"
# include "./shared/constants.hpp"

class Game {
	public:
		Game(int, int);
		~Game();

		std::vector<Vec2> 	getFood() const;
		std::vector<Vec2> 	getSnake() const;
		void	compute(Action::Enum action);

	private:
		Game();
		bool	checkCollision();
		void	initSnake();
		void	initFood();

		int		mapSizeX;
		int		mapSizeY;

		float gameSpeed;
		float gameTick;
		
		std::vector<Vec2> food;
		std::vector<Vec2> snake;
};

#endif