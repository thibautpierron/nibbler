/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nCursesDL.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:42:27 by mchevall          #+#    #+#             */
/*   Updated: 2017/10/30 16:22:52 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESDL_CLASS_HPP
# define NCURSESDL_CLASS_HPP

# include <iostream>
# include <vector>
# include <deque>
# include "../shared/IgraphLib.hpp"
# include "ncursesetup.hpp"

class nCursesDL : public IgraphLib
{

public:
	nCursesDL(int mapX, int mapY);
	nCursesDL( nCursesDL const & );
	virtual ~nCursesDL();

	nCursesDL &	operator=( nCursesDL const & );
	void					display(std::vector<Vec2> food, std::deque<Vec2> snake, bool GameOver);
	virtual Action::Enum	eventManager();
	const char				*toString();

protected:
private:
	nCursesDL();
	int					checkInput() const;
	void				makeBorder() const;
	int					_mapX;
	int					_mapY;
	WINDOW				*map;
	std::vector<Vec2>	_food;
	std::deque<Vec2>	_snake;
	// WINDOW				*ui;
};

extern "C" {
	nCursesDL	*initContext(int, int);
	void		destroyContext(nCursesDL *);
}

#endif