/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MlxDisplay.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:27:30 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/19 09:40:14 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXDISPLAY_HPP
# define MLXDISPLAY_HPP

# include "IgraphLib.hpp"

# include <iostream>
# include <vector>

extern "C" {
	# include <mlx.h>
}


class MlxDisplay : public IgraphLib {
	public:
		MlxDisplay(int, int);
		~MlxDisplay();

		virtual void			display(std::vector<Vec2> food, std::vector<Vec2> snake);
		// virtual Action::Enum	event();
		// virtual void			destroyContext();
	private:
		MlxDisplay();

		int	mapSizeX;
		int mapSizeY;

		void *mlx;
		void *win;
		void *image;

		int	bit;
		int size;
		int end;
		char *data;
};

#endif