/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundDL.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:13:13 by mchevall          #+#    #+#             */
/*   Updated: 2017/10/31 14:26:38 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "soundDL.hpp"
#include <unistd.h>

soundDL::soundDL(bool volume)
{
	SDL_Init(SDL_INIT_AUDIO);
    _frequency = 44100;
    _format = MIX_DEFAULT_FORMAT;
    _channels = MIX_DEFAULT_CHANNELS;
	_chunksize = 1024;
	
	if (volume == true)
		_volume = MIX_MAX_VOLUME;
	else
		_volume = 0;

	_eatfile = "soundDL/sounds/eat.ogg";
	_deathfile = "soundDL/sounds/death.ogg";
	_musicfile = "soundDL/sounds/music.wav";
	_openingfile = "soundDL/sounds/opening.ogg";
	_sfx = NULL;
	int flags = MIX_INIT_OGG;
	Mix_Init(flags);
	Mix_AllocateChannels(2);
	if (Mix_OpenAudio(_frequency, _format, _channels, _chunksize) == -1)
	std::cerr << "Error : " << Mix_GetError() << std::endl;
	Mix_VolumeMusic(_volume);
	Mix_Volume(1,_volume);
	Mix_Volume(2,_volume);
	return;
}

soundDL::soundDL( soundDL const & src )
{
    *this = src;
    return;
}

soundDL::~soundDL()
{
	Mix_FreeChunk(_sfx);
	Mix_FreeMusic(_music);
	Mix_AllocateChannels(0);
	Mix_CloseAudio();
	while(Mix_Init(0))
		Mix_Quit();
	SDL_Quit();
    return;
}

soundDL &		soundDL::operator=( soundDL const & rhs )
{
    if (this != &rhs)
        ;
    return *this;
}

void			soundDL::playSound(SoundAction::Enum action)
{
	switch (action)
	{
		case SoundAction::TOGGLE_SOUND:
			if (Mix_VolumeMusic(-1) == 0)
				_volume = MIX_MAX_VOLUME;
			else
				_volume = 0;
			Mix_VolumeMusic(_volume);
			Mix_Volume(1,_volume);
			Mix_Volume(2,_volume);
			break;
		case SoundAction::DEATH:
			if ((_sfx = Mix_LoadWAV(_deathfile)) == NULL)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			if (Mix_PlayChannel(1, _sfx, 0) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		case SoundAction::EAT:
			if ((_sfx = Mix_LoadWAV(_eatfile)) == NULL)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			if (Mix_PlayChannel(2, _sfx, 0) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		case SoundAction::MUSIC:
			if ((_music = Mix_LoadMUS(_musicfile)) == NULL)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			if (Mix_PlayMusic(_music, -1) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		case SoundAction::OPENING:
			if ((_sfx = Mix_LoadWAV(_openingfile)) == NULL)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			if (Mix_PlayChannel(1, _sfx, 0) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
				usleep(3500000);
			break;
		default: return;
	}
}


soundDL			*initContext(bool volume) {
	return new soundDL(volume);
}

void			destroyContext(soundDL *instance) {
	delete instance;
}

/* Accessors */
