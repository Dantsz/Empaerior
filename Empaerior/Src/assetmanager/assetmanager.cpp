#include "pch.h"
#include "../../Include/assetmanager/assetmanager.h"
#include "../application.h"
#include "../Include/core/core.h"






inline Empaerior::hash_map<Empaerior::string, std::unique_ptr<Mix_Chunk>> Sounds;
inline Empaerior::hash_map<Empaerior::v_pair<Empaerior::string, Empaerior::s_int>,std::shared_ptr<Empaerior::vector<Empaerior::surface_glyph>>,pair_hash> dim_to_glyphs;


namespace Empaerior::Asset_Loading
{







	[[nodiscard]] std::shared_ptr<Empaerior::vector<surface_glyph>> load_glyph_vector(const Empaerior::string& font_path, const Empaerior::s_int& size)
	{
		//search for the glyphs
		auto glyphs = dim_to_glyphs.find({font_path,size});
		//if they haven't been found create them
		if (glyphs == dim_to_glyphs.end())
		{
			std::shared_ptr<Empaerior::vector<surface_glyph>> vec = std::make_shared<Empaerior::vector<surface_glyph>>();
			//all s_glyphs are white
			Empaerior::Color c = { 255,255,255,255 };
			createGlyphs(*vec, font_path, size,c );
			dim_to_glyphs.insert({ {font_path,size},vec });
			return vec;
		}
		else
		{
			return glyphs->second;
		}


	}

	void play_sound(const Empaerior::string& sound_path)
	{
		try {
			auto sound = Sounds.find(sound_path);
			if (sound == Sounds.end())// not found, create new one
			{

				SDL_RWops* rwop;
				rwop = SDL_RWFromFile(sound_path.c_str(), "rb");
				//load the sound in the rwop
				//Mix_LoadWAV(sound_path.c_str())
				if (rwop == nullptr)
				{
					
					throw E_runtime_exception("Cannot find the .wav  file: " + sound_path + ' ', __FILE__, __LINE__, __FUNCTION__);
				}
				std::unique_ptr<Mix_Chunk>TempSound = std::unique_ptr<Mix_Chunk>(Mix_LoadWAV_RW(rwop, 1));

				Sounds.insert({ sound_path,std::move(TempSound) });
				Mix_PlayChannel(-1, &(*Sounds[sound_path]), 0);

			}
			else
			{
				Mix_PlayChannel(-1, &(*sound->second), 0);
			}
		}
		catch (E_runtime_exception & e) {
			// do stuff with exception... 
			e.print_message();
		}
	}

	void set_volume(const Empaerior::s_int n_volume)
	{
		Mix_Volume(-1, n_volume);
	}



	void clear_sounds()
	{
		for (auto i = Sounds.begin(); i != Sounds.end();)
		{

			i->second.reset();
			Sounds.erase(i);
			if (Sounds.empty()) return;
		}

		Sounds.clear();
	}
	
	



	
}