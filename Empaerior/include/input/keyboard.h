#pragma once
#include "../include/core/defines/defines.h"
namespace Empaerior
{


   namespace Input
	{
		namespace Keyboard {

			//TO understand the difference beetween key and phisical key /
			//https://wiki.libsdl.org/CategoryKeyboard
			
			//scancodes
			EMP_FORCEINLINE Empaerior::boole is_key_pressed(const SDL_Scancode& key)
			{
				Empaerior::byte const* keys = SDL_GetKeyboardState(nullptr);
				return keys[key] ? 1 : 0;
			}
			//keycodes
			EMP_FORCEINLINE Empaerior::boole is_physical_key_pressed(const SDL_Keycode& key)
			{
				
				return is_key_pressed(SDL_GetScancodeFromKey(key)) ? 1 : 0;

			}


		}


	}

}