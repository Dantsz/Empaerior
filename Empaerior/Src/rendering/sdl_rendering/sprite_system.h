#pragma once 
#include "../../core/exceptions/exceptions.h"
#include "../../core/ecs/ecs.h"

#include "../../systems/component.h"
#include "rendering/sdl_rendering/objects/sprite.h"

#include "../../input/eventhandler/eventhandler.h"
#include "sdlwrappers/rendering_wrappers.h"

#include <set>

namespace Empaerior::SDL_Rendering
{
	//the purpose of this system is to be a more cache_friendly approach to the Spr_system
	class Sprite_System : public Empaerior::System
	{
	public:


		size_t emplace_sprite(Empaerior::ECS& ecs, const Empaerior::u_inter& id,
			const Empaerior::Float_Rect& m_rect,
			const Empaerior::Int_Rect& m_tex_rect,
			const Empaerior::string& tex_path
		)
		{

			size_t index = sprites.emplace_back();

			//make the default animation
			size_t animation_index = animations.push_back({ m_tex_rect });

			//set the default animation chain
			sprites.objects[index].animation_begin = animation_index;
			sprites.objects[index].cur_frame = animation_index;//end it , it only has one frame
			sprites.objects[index].animation_end = animation_index;//


			//set the next frame in the animation, 
			//in this case , as we only load one frame, the next frame is actually the current frame
			animations.objects[animation_index].next_animation = animation_index;
			sprites.objects[index].default_anim_frame = animation_index;

			Empaerior::SpriteFunctions::InitSprite(sprites.objects[index], m_rect, tex_path);



			ecs.get_component<Empaerior::Sprite_Component>(id).sprite_indexes.push_back(index);


			return ecs.get_component<Empaerior::Sprite_Component>(id).sprite_indexes.size() - 1;

		}

		size_t emplace_textsprite(Empaerior::ECS& ecs, const Empaerior::u_inter& id,
			const Empaerior::Float_Rect& m_rect,
			const Empaerior::string& font_path,
			const Empaerior::u_int& m_size,
			const Empaerior::string& message,
			Empaerior::Color m_color)
		{
			size_t index = sprites.push_back({});
			size_t animation_index = animations.push_back({ {0,0,static_cast<Empaerior::s_int>(m_rect.dimensions.w),static_cast<Empaerior::s_int>(m_rect.dimensions.h) } });
			//set the next frame in the animation, 
			//in this case , as we only load one frame, the next frame is actually the current frame
			animations.objects[animation_index].next_animation = animation_index;
			sprites.objects[index].default_anim_frame = animation_index;

			Empaerior::SpriteFunctions::InitTextSprite(sprites.objects[index], m_rect, font_path, m_size, message, m_color);

			//set the default animation chain
			sprites.objects[index].animation_begin = animation_index;
			sprites.objects[index].cur_frame = animation_index;//end it , it only has one frame
			sprites.objects[index].animation_end = animation_index;//


			ecs.get_component<Empaerior::Sprite_Component>(id).sprite_indexes.push_back(index);



			return ecs.get_component<Empaerior::Sprite_Component>(id).sprite_indexes.size() - 1;

		}


		void update(Empaerior::ECS& ecs, const Empaerior::u_int& dt);
		void render(Empaerior::ECS& ecs, Empaerior::Camera& camera);


		//adds another frame to the animation chain of the sprite
		//index - the index of the sprite in the system's vector
		//a method to get the index is by using the index vector of the sprite_component;



		//creates a frame and returns the index that frame in the animation vector  
		void create_animation(Empaerior::Sprite_Component::Animation_Entry& entry, Empaerior::Int_Rect frame)
		{

			size_t animation_index = animations.push_back({ frame });
			//make the next frame this frame
			animations.objects[animation_index].next_animation = animation_index;

			entry.anim_begin = animation_index;
			entry.anim_end = animation_index;



		}
		//appends the frame to the end of the animation
		size_t append_frame(Empaerior::Sprite_Component::Animation_Entry& entry, Empaerior::Int_Rect frame)
		{
			//create a new frame
			size_t new_anim = animations.push_back({ {frame}, });
			//set the last frame to repeat indefinetely
			animations.objects[new_anim].next_animation = new_anim;
			//put the animation in the chain
			animations.objects[entry.anim_end].next_animation = new_anim;
			entry.anim_end = new_anim;

			return new_anim;

		}

		void delete_animation(Empaerior::Sprite_Component::Animation_Entry& entry)
		{
			//stack
			std::set<size_t> to_free;
			//insert the first
			to_free.insert(entry.anim_begin);
			//keep the next
			size_t next = animations.objects[entry.anim_begin].next_animation;

			//while the end isn't reached
			//loop the chain
			while (to_free.find(next) == to_free.end())
			{
				//insert the next
				to_free.insert(next);
				//go to the next
				next = animations.objects[next].next_animation;
			}

			//delete all in the chain
			for (const auto& a : to_free)
			{
				animations.remove(a);
			}



		}

		//makes the animation chain loop
		EMP_FORCEINLINE void make_animation_loop(Empaerior::Sprite_Component::Animation_Entry& entry)
		{

			animations.objects[entry.anim_end].next_animation = entry.anim_begin;

		}

		void set_sprite_animation(Empaerior::u_inter sprite_id, Empaerior::Sprite_Component::Animation_Entry& entry)
		{
			sprites.objects[sprite_id].animation_begin = entry.anim_begin;
			sprites.objects[sprite_id].cur_frame = entry.anim_begin;
			sprites.objects[sprite_id].animation_end = entry.anim_end;
		}
		//remove the sprites and animations
		void OnEntityRemovedfromSystem(Empaerior::ECS* ecs, const Empaerior::u_inter& entity_id) override
		{
			//for all sprites
			for (auto& sprite : ecs->get_component<Empaerior::Sprite_Component>(entity_id).sprite_indexes)
			{
				//remove the default frame
				animations.remove(sprites.objects[sprite].default_anim_frame);
				//remove the sprite
				sprites.remove(sprite);
			}
			//delete all animations
			for (auto& animations : ecs->get_component<Empaerior::Sprite_Component>(entity_id).animation_index.objects)
			{
				delete_animation(animations);
			}

		}

		//deletes both sprites and textsprites
		EMP_FORCEINLINE	void delete_sprite(size_t sprite_id)
		{
			//remove the default  animation
			animations.remove(sprites[sprite_id].default_anim_frame);
			//removethe sprite
			sprites.remove(sprite_id);
		}

		//
		EMP_FORCEINLINE Empaerior::Graphic_element& get_sprite(Empaerior::u_inter index)
		{
			return sprites.objects[index];
		}



		//all sprites		
		unsafe_vector<Empaerior::Graphic_element> sprites;
		unsafe_vector<Animation> animations;



	};
}
