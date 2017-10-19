/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MlxDisplay.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:54:25 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/19 10:13:20 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MlxDisplay.hpp"

MlxDisplay::MlxDisplay(int mapSizeX, int mapSizeY) :
	mapSizeX(mapSizeX), mapSizeY(mapSizeY) {
		std::string title("Nibbler (mlx)");
		
		char * cstr = new char [title.length()+1];
		std::strcpy (cstr, title.c_str());
	
		mlx = mlx_init();
		win = mlx_new_window(mlx, 500, 500, cstr);
		image = mlx_new_image(mlx, 500, 500);

		data = mlx_get_data_addr(image, &bit, &size, &end);
}

MlxDisplay::~MlxDisplay() {
	return;
}

void	MlxDisplay::display(std::vector<Vec2> food, std::vector<Vec2> snake) {

	Vec2 v;

	food.push_back(v);
	snake.push_back(v);
	
	for (unsigned int i = 0; i < 500; i++) {
		data[i * size + i * bit / 8] = 40;
		data[i * size + i * bit / 8 + 1] = 100;
		data[i * size + i * bit / 8 + 2] = -86;
	}

	mlx_put_image_to_window(mlx, win, image, 0, 0);
	mlx_loop(mlx);
}

MlxDisplay	*initContext(int mapSizeX, int mapSizeY) {
	return new MlxDisplay(mapSizeX, mapSizeY);
}

void		destroyContext(MlxDisplay *instance) {
	delete instance;
}