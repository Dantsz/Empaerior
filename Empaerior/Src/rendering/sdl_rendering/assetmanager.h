#pragma once
#include <memory>
#include <unordered_map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
#include "../../core/defines/basic_defines.h"

namespace Empaerior::Asset_Loading
{

	//texture
	std::shared_ptr<SDL_Texture>  load_texture_from_file(const Empaerior::string& tex_path);
	std::shared_ptr<SDL_Texture> load_texture_from_memory(void* mem, Empaerior::s_int size);

	//clear ununsed
	void clean_textures();



	//clear all
	void clear_textures();

}