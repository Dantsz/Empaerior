#pragma once
#include <memory>
#include <unordered_map>
#include <SDL.h>
#include <SDL_mixer.h>
#include "rendering/sdl_rendering/sdl_renderer.h"

//Test



namespace Empaerior::Asset_Loading
{

	//texture
	std::shared_ptr<SDL_Texture>  load_texture_from_file(const Empaerior::string& tex_path);
	std::shared_ptr<SDL_Texture> load_texture_from_memory(void* mem, Empaerior::s_int size);
	//font


	std::shared_ptr<Empaerior::vector<surface_glyph>> load_glyph_vector(const Empaerior::string& font_path, const Empaerior::s_int& size);

	//sound   
	 void play_sound(const Empaerior::string& sound_path);
	 void set_volume(const Empaerior::s_int n_volume);




	 void clear_sounds();
	



	 



};