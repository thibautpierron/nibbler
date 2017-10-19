/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IgraphLib.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:38:33 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/19 14:16:25 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGRAPHLIB_HPP
# define IGRAPHLIB_HPP

# include <vector>

# include "constants.hpp"

struct Vec2 {
	int x;
	int y;
	Vec2() : x(0), y(0) {}
	Vec2(int x, int y) : x(x), y(y) {}
};

class IgraphLib {
	public:
		virtual void			display(std::vector<Vec2> food, std::vector<Vec2> snake) = 0;
		virtual Action::Enum	eventManager() = 0;
};

#endif