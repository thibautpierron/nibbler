/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundDL.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:13:51 by mchevall          #+#    #+#             */
/*   Updated: 2017/10/30 17:38:42 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUNDDL_CLASS_HPP
# define SOUNDDL_CLASS_HPP

# include <iostream>
# include "../shared/IsoundLib.hpp"

# include <SDL.h>
# include <SDL_mixer.h>

class soundDL : public IsoundLib
{

public:
	soundDL(const char *file);
	soundDL( soundDL const & );
	virtual ~soundDL();
	
	soundDL &	operator=( soundDL const & );
	void		playSound(const char *sound);	
protected:
private:
	soundDL();
	int			_frequency;
	uint16_t	_format;
	int			_channels;
	int			_chunksize;
	Mix_Music*	_music;


};


extern "C" {
	soundDL		*initContext(const char *file);
	void		destroyContext(soundDL *);
}

#endif