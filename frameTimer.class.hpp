/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frameTimer.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:43:00 by fdexheim          #+#    #+#             */
/*   Updated: 2017/11/07 14:27:14 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAMETIMERCLASS_H
# define FRAMETIMERCLASS_H

#include <unistd.h>
#include <ctime>

class			frameTimer
{
public:
	frameTimer();
	frameTimer(float fpsInit);
	virtual ~frameTimer();
	frameTimer(frameTimer const & src);

	frameTimer &		operator=(frameTimer const & src);

	void				updateTimeBeginningLoop();
	void				updateTimeEndLoop();

	float				fps;
	clock_t				frameTime;
	clock_t				time;
	clock_t				beg;
	unsigned long		frameNumber;

private:
	static int			_nb_frameTimer;
};

#endif
