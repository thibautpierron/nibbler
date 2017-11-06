/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundDL.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:13:51 by mchevall          #+#    #+#             */
/*   Updated: 2017/11/06 18:24:57 by mchevall         ###   ########.fr       */
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
	soundDL(bool volume);
	soundDL( soundDL const & );
	virtual ~soundDL();
	
	soundDL &		operator=( soundDL const & );
	void			playSound(SoundAction::Enum action);
protected:
private:
	soundDL();
	int			_frequency;
	uint16_t	_format;
	int			_channels;
	int			_chunksize;
	Mix_Music*	_music;
	Mix_Chunk*	_sfxeat;
	Mix_Chunk*	_sfxdeath;
	Mix_Chunk*	_sfxopening;
	std::string	_musicfile;
	std::string	_deathfile;
	std::string	_eatfile;
	std::string	_openingfile;
	int			_volume;
};


extern "C" {
	soundDL		*initContext(bool volume);
	void		destroyContext(soundDL *);
}

#endif