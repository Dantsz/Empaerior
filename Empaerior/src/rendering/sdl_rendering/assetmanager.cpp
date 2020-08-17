#include "assetmanager.h"
#include "../../core/exceptions/exceptions.h"
#include "../sdl_rendering/sdlwrappers/sdl_wrappers.h"
#include "../sdl_rendering/sdlwrappers/ptr_wrappers.h"
#include "../../core/utilities/hash/emp_hash.h"
#include "objects/sprite.h"
#include "sdl_renderer.h"

inline Empaerior::hash_map<Empaerior::string, std::shared_ptr<SDL_Texture>> Textures;
namespace Empaerior::Asset_Loading
{

	[[nodiscard]] std::shared_ptr<SDL_Texture> load_texture_from_file(const Empaerior::string& tex_path)//returnsnullptr on  exception
	{
		//I Had to rewrite this whole fucking things so please don't have leaks....
		//search for texture
		auto tex = Textures.find(tex_path);
		if (tex == Textures.end())
		{
			try {
				//if not found create the texture		
				SDL_RWops* rwop;
				rwop = SDL_RWFromFile(tex_path.c_str(), "rb");
				if (rwop == nullptr) // if the file doesn't exists throws exception
				{

					throw E_runtime_exception("File:  " + tex_path + " not found", __FILE__, __LINE__, __FUNCTION__);

				}

				
				if (IMG_isPNG(rwop) || IMG_isBMP(rwop) || IMG_isJPG(rwop))  // if the  image is a good png
				{
					//create atextureand free the rwop
					std::shared_ptr<SDL_Texture> tex_p = sdl_shared(IMG_LoadTexture_RW(Empaerior::SDL_Rendering::get_renderer(), rwop, 1));

					Textures.insert({ tex_path,tex_p });  // put texture in  map

					return tex_p;
				}
				else
				{

					//delete rwop
					SDL_RWclose(rwop);
					//send the exception
					throw E_runtime_exception("File:  " + tex_path + "  is not a supported type", __FILE__, __LINE__, __FUNCTION__);

				}


			}
			catch (E_runtime_exception& e) {
				// do stuff with exception... 
				e.print_message();
				//return a nullpointer
				return nullptr;
			}


		}
		else
		{

			//if found 
			return tex->second;

		}



	}

	std::shared_ptr<SDL_Texture> load_texture_from_memory(void* mem, Empaerior::s_int size)
	{

		std::string name = Empaerior::Hash::sha256_data(mem, size);
		auto tex = Textures.find(name);
		if (tex == Textures.end())
		{
			try {
				//if not found create the texture		
				SDL_RWops* rwop;
				rwop = SDL_RWFromMem(mem, size);
				if (rwop == nullptr) // if the file doesn't exists throws exception
				{

					throw E_runtime_exception("Couldn't load :  " + name, __FILE__, __LINE__, __FUNCTION__);

				}


				if (IMG_isPNG(rwop) || IMG_isBMP(rwop) || IMG_isJPG(rwop))  // if the  image is a good png
				{
					//create atextureand free the rwop
					std::shared_ptr<SDL_Texture> tex_p = sdl_shared(IMG_LoadTexture_RW(Empaerior::SDL_Rendering::get_renderer(), rwop, 1));

					Textures.insert({ name,tex_p });  // put texture in  map

					return tex_p;
				}
				else
				{

					//delete rwop
					SDL_RWclose(rwop);
					//send the exception
					throw E_runtime_exception("Soemthing went wrong loading :  " + name + "  is not a support type", __FILE__, __LINE__, __FUNCTION__);

				}


			}
			catch (E_runtime_exception& e) {
				// do stuff with exception... 
				e.print_message();
				//return a nullpointer
				return nullptr;
			}



		}
		else
		{
			return tex->second;
		}
	}
		
	void clean_textures()
	{

			for (auto i = Textures.begin(); i != Textures.end(); )
			{

				if (i->second.use_count() == 1)
				{

					i = Textures.erase(i);
				}
				else
				{
					++i;
				}
			}

	}


	

	void clear_textures()
	{
		for (auto i = Textures.begin(); i != Textures.end();)
		{

			i->second.reset();
			i = Textures.erase(i);
			if (Textures.empty()) return;
		}

		Textures.clear();
	}

}