#pragma once
//TOOL THAT INTEGRATES TMXLITE INTO EMPAERIOR
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Property.hpp>
#include <Empaerior.h>

namespace Empaerior
{
	namespace Tmx
	{

		struct Map
		{
			std::vector<Empaerior::u_inter> tile_layer;	

		};

		void create_map(Empaerior::ECS& ecs, std::shared_ptr<Empaerior::Sprite_System>& spr_system, const std::string& path, Empaerior::Tmx::Map& e_map);

		

	//	makes and entity that has as a spr_component which has as sprites the tiles of the layer
		void make_finite_tile_layer(Empaerior::ECS& ecs, Empaerior::Tmx::Map& e_map, tmx::Map& map, const tmx::TileLayer& tiles, std::shared_ptr<Empaerior::Sprite_System>& spr_system);
	

		void make_infinite_tile_layer(Empaerior::ECS& ecs, Empaerior::Tmx::Map& e_map, tmx::Map& map, const tmx::TileLayer& tiles, std::shared_ptr<Empaerior::Sprite_System>& spr_system);





	}


}