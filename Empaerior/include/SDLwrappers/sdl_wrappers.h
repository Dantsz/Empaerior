#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include "core/defines/basic_defines.h"


namespace SDLW {
	//defines constexprs
	constexpr uint16_t sdl = 1<<0;
	constexpr uint16_t sdl_image =  1<<1;
	constexpr uint16_t sdl_ttf=  1<<2;
	constexpr uint16_t sdl_mix = 1<<3;

	EMP_FORCEINLINE uint16_t Init()
	{
		uint16_t flags = 0;
		
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			flags |= sdl;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		{
			flags |=sdl_mix;
		}


		return flags;
	}
	EMP_FORCEINLINE void Quit()
	{

		Mix_Quit();
		SDL_Quit();

	}

}
