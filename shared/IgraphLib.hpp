/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IgraphLib.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:38:33 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/27 14:25:52 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGRAPHLIB_HPP
# define IGRAPHLIB_HPP

# include <vector>
# include <deque>

# include "constants.hpp"

struct Vec2 {
	int x;
	int y;
	Vec2() : x(0), y(0) {}
	Vec2(int x, int y) : x(x), y(y) {}
};

class IgraphLib {
	public:
		virtual void			display(std::vector<Vec2> food, std::deque<Vec2> snake) = 0;
		virtual Action::Enum	eventManager() = 0;
		virtual const char		*toString() = 0;
};

#endif