/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IgraphLib.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:38:33 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/19 10:51:09 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGRAPHLIB_HPP
# define IGRAPHLIB_HPP

# include <vector>

# include "constants.hpp"

struct Vec2 {
	int x;
	int y;
};

class IgraphLib {
	public:
		// virtual void			initContext(int, int) = 0;
		virtual void			display(std::vector<Vec2> food, std::vector<Vec2> snake) = 0;
		// virtual Action::Enum	event() = 0;
		// virtual void			destroyContext() = 0;
};

#endif