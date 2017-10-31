/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundDL.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:13:13 by mchevall          #+#    #+#             */
/*   Updated: 2017/10/31 11:47:12 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "soundDL.hpp"

soundDL::soundDL()
{
	SDL_Init(SDL_INIT_AUDIO);
    _frequency = 44100;
    _format = MIX_DEFAULT_FORMAT;
    _channels = MIX_DEFAULT_CHANNELS;
	_chunksize = 1024;
	
	_eatfile = "soundDL/eat.mp3";
	_deathfile = "soundDL/death.mp3";
	_musicfile = "soundDL/music.wav";
	Mix_Init(MIX_INIT_MP3);
	if (Mix_OpenAudio(_frequency, _format, _channels, _chunksize) == -1)
	std::cerr << "Error : Mix_OpenAudio failed to open audio channel" << std::endl;
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	playSound(SoundAction::MUSIC);
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
				Mix_VolumeMusic(MIX_MAX_VOLUME);
			else
				Mix_VolumeMusic(0);
			break;
		case SoundAction::DEATH:
			if ((_sfx = Mix_LoadMUS(_deathfile)) == NULL)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			if (Mix_PlayMusic(_sfx, 1) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		case SoundAction::EAT:
			if ((_sfx = Mix_LoadMUS(_eatfile)) == NULL)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			if (Mix_PlayMusic(_sfx, 1) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		case SoundAction::MUSIC:
			if ((_music = Mix_LoadMUS(_musicfile)) == NULL)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			if (Mix_PlayMusic(_music, -1) == -1)
				std::cerr << "Error : " << Mix_GetError() << std::endl;
			break;
		default: return;
	}
}


soundDL			*initContext() {
	return new soundDL();
}

void			destroyContext(soundDL *instance) {
	delete instance;
}

/* Accessors */
