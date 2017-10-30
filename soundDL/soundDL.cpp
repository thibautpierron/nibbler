/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundDL.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:13:13 by mchevall          #+#    #+#             */
/*   Updated: 2017/10/30 19:05:52 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "soundDL.hpp"

soundDL::soundDL(){;}

soundDL::soundDL(const char *file)
{
	SDL_Init(SDL_INIT_AUDIO);
    _frequency = 44100;
    _format = MIX_DEFAULT_FORMAT;
    _channels = MIX_DEFAULT_CHANNELS;
	_chunksize = 1024;
	playSound(file);

    return;
}

soundDL::soundDL( soundDL const & src )
{
    *this = src;
    return;
}

soundDL::~soundDL()
{
	Mix_FreeMusic(_music);
    Mix_CloseAudio();
	SDL_Quit();
    return;
}

soundDL &	soundDL::operator=( soundDL const & rhs )
{
    if (this != &rhs)
        ;
    return *this;
}

void		soundDL::playSound(const char * file)
{
	if (Mix_OpenAudio(_frequency, _format, _channels, _chunksize) == -1)
		std::cerr << "Error : Mix_OpenAudio failed to open audio channel" << std::endl;
	if ((_music = Mix_LoadMUS(file)) == NULL)
	{
		std::cerr << "Error : " << Mix_GetError() << std::endl;
		// std::cerr << "Error : Mix_LoadMus failed to open \"" << file << "\"" << std::endl;
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	if (Mix_PlayMusic(_music, -1) == -1)
		std::cerr << "Error : Mix_PlayMusic failed to play music" << std::endl;
	
}

soundDL		*initContext(const char *file) {
	return new soundDL(file);
}

void		destroyContext(soundDL *instance) {
	delete instance;
}

/* Accessors */
