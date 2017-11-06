/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frameTimer.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:43:00 by fdexheim          #+#    #+#             */
/*   Updated: 2017/11/06 14:04:09 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frameTimer.class.hpp"

frameTimer::frameTimer() { _nb_frameTimer++; return; }
frameTimer::~frameTimer() { _nb_frameTimer--; return; }
frameTimer::frameTimer(frameTimer const & src)
{
	_nb_frameTimer++;
	*this = src;
	return;
}

frameTimer::frameTimer(float fpsInit) : fps(fpsInit)
{
	_nb_frameTimer++;

	this->frameTime = 1000000 / this->fps;
	this->time = 0;
	this->beg = 0;
	this->frameNumber = 0;

	return;
}

frameTimer&		frameTimer::operator=(frameTimer const &src)
{
	this->fps = src.fps;
	this->frameTime = src.frameTime;
	this->time = src.time;
	this->beg = src.beg;
	this->frameNumber = src.frameNumber;

	return (*this);
}


void			frameTimer::updateTimeBeginningLoop()
{
	this->frameNumber++;
	this->beg = std::clock();
}

void			frameTimer::updateTimeEndLoop()
{
	double diff;
	this->time = std::clock();
	diff = difftime(this->time, this->beg);
	if (diff < this->frameTime)
		usleep(this->frameTime - diff);
}

int				frameTimer::_nb_frameTimer = 0;