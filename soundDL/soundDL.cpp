/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundDL.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:13:13 by mchevall          #+#    #+#             */
/*   Updated: 2017/11/06 20:02:15 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "soundDL.hpp"
#include <unistd.h>

soundDL::soundDL(bool volume)
{
	SDL_InitSubSystem(SDL_INIT_AUDIO);
    _frequency = 44100;
    _format = MIX_DEFAULT_FORMAT;
    _channels = 1;
	_chunksize = 1024;
	
	if (volume == true)
		_volume = MIX_MAX_VOLUME;
	else
		_volume = 0;

	_eatfile = "soundDL/sounds/eat.ogg";
	_deathfile = "soundDL/sounds/death.ogg";
	_musicfile = "soundDL/sounds/music.wav";
	_openingfile = "soundDL/sounds/opening.ogg";
	int flags = MIX_INIT_OGG;
	Mix_Init(flags);
	if (Mix_OpenAudio(_frequency, _format, _channels, _chunksize) == -1)
		std::cerr << "Error : " << Mix_GetError() << std::endl;
	if ((_sfxeat = Mix_LoadWAV(_eatfile.c_str())) == NULL)
		std::cerr << "Error : " << Mix_GetError() << std::endl;
	if ((_sfxdeath = Mix_LoadWAV(_deathfile.c_str())) == NULL)
		std::cerr << "Error : " << Mix_GetError() << std::endl;
	if ((_sfxopening = Mix_LoadWAV(_openingfile.c_str())) == NULL)
		std::cerr << "Error : " << Mix_GetError() << std::endl;
	if ((_music = Mix_LoadMUS(_musicfile.c_str())) == NULL)
		std::cerr << "Error : " << Mix_GetError() << std::endl;
	Mix_VolumeMusic(_volume);
	Mix_Volume(-1,_volume);
	return;
}

soundDL::soundDL( soundDL const & src )
{
    *this = src;
    return;
}

soundDL::~soundDL()
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	Mix_FreeChunk(_sfxeat);
	_sfxeat = NULL;
	Mix_FreeChunk(_sfxdeath);
	_sfxdeath = NULL;
	Mix_FreeChunk(_sfxopening);
	_sfxopening = NULL;
	Mix_FreeMusic(_music);
	_music = NULL;
	Mix_AllocateChannels(0);
	while (Mix_QuerySpec(&_frequency, &_format, &_channels) > 0)
		Mix_CloseAudio();
	while(Mix_Init(0))
		Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
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
			Mix_Volume(-1,_volume);
			break;
		case SoundAction::DEATH:
			if (Mix_PlayChannel(-1, _sfxdeath, 0) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		case SoundAction::EAT:
			Mix_HaltChannel(-1);
			if (Mix_PlayChannel(-1, _sfxeat, 0) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		case SoundAction::MUSIC:
			if (Mix_PlayMusic(_music, -1) == -1)
			std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		case SoundAction::OPENING:
			if (Mix_PlayChannel(1, _sfxopening, 0) == -1)
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
