#include "pch.h"
#include "EmpTmxlite.h"


void Empaerior::Tmx::create_map(Empaerior::ECS& ecs, std::shared_ptr<Empaerior::Sprite_System>& spr_system, const std::string& path, Empaerior::Tmx::Map& e_map)

{
	//create a tmxlite map
	tmx::Map map;
	map.load(path);
	
	const auto& layers = map.getLayers();


	//go through layers
	for (const auto& layer : layers)
	{

		//parsing non infinite stuff
		if (layer->getType() == tmx::Layer::Type::Tile)
		{
			if (map.getInfinity() == false)
			{
				const auto& tiles = layer->getLayerAs<tmx::TileLayer>();
				make_finite_tile_layer(ecs, e_map, map, tiles, spr_system);
			}
			else
			{
				const auto& tiles = layer->getLayerAs<tmx::TileLayer>();
				make_infinite_tile_layer(ecs, e_map, map, tiles, spr_system);
			}
			
		}

	}


}
void Empaerior::Tmx::make_finite_tile_layer(Empaerior::ECS& ecs, Empaerior::Tmx::Map& e_map, tmx::Map& map, const tmx::TileLayer& tiles, std::shared_ptr<Empaerior::Sprite_System>& spr_system)
{
	//create a new entity for each layer
	Empaerior::u_inter tile_layer = ecs.create_entity_ID();
	e_map.tile_layer.push_back(tile_layer);
	ecs.add_component<Empaerior::Sprite_Component>(tile_layer, {});

	for (auto i = 0; i < map.getTileCount().x; i++)
	{
		for (auto j = 0; j < map.getTileCount().y; j++)
		{
			if (tiles.getTiles()[i * map.getTileCount().y + j].ID == 0) continue;
			
			const tmx::Tileset* tile_set = nullptr;
			//search trough tilesets until matching tileset to uid is found
			for (auto x = 0; x < map.getTilesets().size(); x++)
			{
				if (map.getTilesets()[x].hasTile(tiles.getTiles()[i * map.getTileCount().y + j].ID))
				{
					tile_set = &(map.getTilesets()[x]);
				}
			}
			if (tile_set == nullptr) ENGINE_CRITICAL("TILESET ERROR");
			auto* act_tile = tile_set->getTile(tiles.getTiles()[i * map.getTileCount().y + j].ID);

			auto width = tile_set->getColumnCount();
			int height = tile_set->getTileCount() / width;


			
			spr_system->emplace_sprite(ecs, tile_layer,

				{ float(j * map.getTileSize().x),float(i * map.getTileSize().y),float(tile_set->getTileSize().x),float(tile_set->getTileSize().y) },

								{
								 static_cast<int>( (tiles.getTiles()[i * map.getTileCount().y + j].ID - tile_set->getFirstGID()  )  % width ) * static_cast<int>(tile_set->getTileSize().x),  

								static_cast<int>( (tiles.getTiles()[i * map.getTileCount().y + j].ID - tile_set->getFirstGID())  / width) * static_cast<int>(tile_set->getTileSize().x),

								static_cast<int>(tile_set->getTileSize().x),
								static_cast<int>(tile_set->getTileSize().y)

								}

								, tile_set->getImagePath() );
			//std::cout  <<'\n' << static_cast<int>((tiles.getTiles()[i * map.getTileCount().y + j].ID - tile_set->getFirstGID()) % width) * static_cast<int>(tile_set->getTileSize().x)
			//	<< " " << static_cast<int>((tiles.getTiles()[i * map.getTileCount().y + j].ID - tile_set->getFirstGID()) / width) * static_cast<int>(tile_set->getTileSize().x)
			//	<< " "
			//	<< static_cast<int>(tile_set->getTileSize().x) << " " << static_cast<int>(tile_set->getTileSize().y) << '\n';
		
				

		
		}


	}


}

void Empaerior::Tmx::make_infinite_tile_layer(Empaerior::ECS& ecs, Empaerior::Tmx::Map& e_map, tmx::Map& map, const tmx::TileLayer& tiles, std::shared_ptr<Empaerior::Sprite_System>& spr_system)
{
	//create a new entity for each layer
	Empaerior::u_inter tile_layer = ecs.create_entity_ID();
	e_map.tile_layer.push_back(tile_layer);
	ecs.add_component<Empaerior::Sprite_Component>(tile_layer, {});

	for (const auto& chunk : tiles.getChunks())
	{
		auto begin_x = chunk.x;
		auto begin_y = chunk.y;
		auto c_width = chunk.width;
		auto c_height = chunk.height;
		for (int i = 0; i < c_width; i++)
		{
			for (int j = 0; j < c_height; j++)
			{
				if (chunk.tile_data[i * c_height + j].ID == 0) continue;
				const tmx::Tileset* tile_set = nullptr;
				//search trough tilesets until matching tileset to uid is found
				for (auto x = 0; x < map.getTilesets().size(); x++)
				{
					if (map.getTilesets()[x].hasTile(chunk.tile_data[i * c_height + j].ID))
					{
						tile_set = &(map.getTilesets()[x]);
					}
				}
				if (tile_set == nullptr) ENGINE_CRITICAL("TILESET ERROR");


				auto* act_tile = tile_set->getTile(chunk.tile_data[i * c_height + j].ID);
				auto width = tile_set->getColumnCount();
				int height = tile_set->getTileCount() / width;



				spr_system->emplace_sprite(ecs, tile_layer,

					{ float((begin_x +  j) *  float(map.getTileSize().x)),float((begin_y + i) * float(map.getTileSize().y)),float(tile_set->getTileSize().x),float(tile_set->getTileSize().y) },

								{
								 static_cast<int>((chunk.tile_data[i * c_height + j].ID - tile_set->getFirstGID()) % width) * static_cast<int>(tile_set->getTileSize().x),

								static_cast<int>((chunk.tile_data[i * c_height + j].ID - tile_set->getFirstGID()) / width) * static_cast<int>(tile_set->getTileSize().x),

								static_cast<int>(tile_set->getTileSize().x),
								static_cast<int>(tile_set->getTileSize().y)

								}

								, tile_set->getImagePath());

				//std::cout << ((begin_y + j) * float(map.getTileSize().x)) << ' ' << ((begin_x + i) * float(map.getTileSize().y)) << '\n';

			}



		}

	}
}
