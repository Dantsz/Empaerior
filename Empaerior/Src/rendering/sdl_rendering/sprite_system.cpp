#include "sprite_system.h"
#include "core/utilities/timer.h"
#include "../window.h"
#include "rendering/sdl_rendering/sdl_renderer.h"
namespace Empaerior::SDL_Rendering
{
#define COMPONENT ecs.get_component<Empaerior::Sprite_Component>(id)
	void Empaerior::SDL_Rendering::Sprite_System::update(Empaerior::ECS& ecs, const Empaerior::u_int& dt)
	{

		auto container = ecs.component_manager->get_container<Empaerior::Sprite_Component>();
		Empaerior::Timer timy;
		timy.start();
		for (auto& id : entities_id)
		{

			auto& c_sprites = container->components[id].sprite_indexes;
			for (auto& spr : c_sprites)
			{

				sprites.objects[spr].time += dt; // add the time passed
				while (sprites.objects[spr].time >= sprites.objects[spr].holdTime)// check if the necesarry time passed
				{
					sprites.objects[spr].time -= sprites.objects[spr].holdTime;
					//Advance in the animation
					sprites.objects[spr].cur_frame = animations.objects[sprites.objects[spr].cur_frame].next_animation;

				}

			}



		}



		std::cout << "Update took : " << timy.getTicks() << " ms\n";
	}

	//this is used to calculate the postion of a sprite for rendering
	static inline Empaerior::Float_Rect_S rendering_rect;
	void Empaerior::SDL_Rendering::Sprite_System::render(Empaerior::ECS& ecs, Empaerior::Camera& camera)
	{
		auto container = ecs.component_manager->get_container<Empaerior::Sprite_Component>();

		for (auto& id : entities_id)
		{


			for (auto& spr : container->components[id].sprite_indexes)
			{


				rendering_rect = { sprites.objects[spr].rect.dimensions.x - camera.rect.x, sprites.objects[spr].rect.dimensions.y - camera.rect.y, sprites.objects[spr].rect.dimensions.w, sprites.objects[spr].rect.dimensions.h };
				//setting the texture's color, because each sprite that uses the texture uses it differently (or not)
				SDL_SetTextureColorMod(sprites.objects[spr].texture.get(), sprites.objects[spr].r, sprites.objects[spr].g, sprites.objects[spr].b);//Safe/acceptable to call SDL_SetTextureColorMod a lot?
				//render it


				Empaerior::Render::RenderEx(
					Empaerior::SDL_Rendering::get_renderer(),
					&(*sprites.objects[spr].texture),
					SDL_FLIP_NONE, sprites.objects[spr].rect.angle,
					0,
					&animations.objects[sprites.objects[spr].cur_frame].rect,
					&rendering_rect);

			}


		}

	}
#undef COMPONENT
}
