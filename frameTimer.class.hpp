/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frameTimerClass.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdexheim <fdexheim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:43:00 by fdexheim           #+#    #+#            */
/*   Updated: 2017/10/06 20:00:25 by fdexheim         ###   ########.fr       */
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
	~frameTimer();
	frameTimer(frameTimer const & src);

	frameTimer &		operator=(frameTimer const & src);

	void				updateTimeBeginningLoop();
	void				updateTimeEndLoop(); // stalls if necessary

	float				fps;
	clock_t				frameTime;
	clock_t				time;
	clock_t				beg;
	unsigned long		frameNumber;

private:
	static int			_nb_frameTimer;
};

#endif
