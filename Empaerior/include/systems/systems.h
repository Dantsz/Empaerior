#pragma once

#include "../include/core/exceptions/exceptions.h"


#include "../include/core/ecs/ecs.h"

#include "component.h"

#include "../include/input/eventhandler/eventhandler.h"


#include <memory>
#include <set>
#include "../include/rendering/vulkan_rendering/renderer.h"

namespace Empaerior
{

	class Event_System 
	{
	public:

		~Event_System() = default;
		
		/*
		Adds an event to be listened to by the entity's event listener component
		*/
		void add_event_to_entity(Empaerior::ECS& ecs, const Empaerior::u_inter& entity_id, const Empaerior::u_int& event_type, std::function<void(Empaerior::Event&)> function , Empaerior::s_int call_times = -1)
		{
#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(entity_id).event_listener
			EVENTLISTENER.register_event(event_type, function, call_times);
#undef EVENTLISTENER
		}


		void handle_events(Empaerior::ECS& ecs,Empaerior::Event& event)
		{
#define EVENTLISTENER  ecs.get_component<Empaerior::Event_Listener_Component>(*Iterator).event_listener
			//REVERSE ITERATOR
			std::vector<Empaerior::u_inter>::reverse_iterator Iterator = entityList->entities_id.rbegin();
			//ITERATING THROUGH THE ENTITIES IN REVERSE
			while (Iterator != entityList->entities_id.rend() && !Empaerior::is_event_handled(event))
			{
				EVENTLISTENER.handleEvents(event);
				Iterator++;
			}
			
			
			
			
#undef EVENTLISTENER

		}
		public:
		std::shared_ptr<Empaerior::EntitySystemList> entityList;



	};

	

	

	class T_E_System 
	{
	public:

		~T_E_System() = default;
		

		using Timed_Function = std::function<void()>;


		//Adds a function to the container
		//time = the time between this function and the time *function* is called
		//call_number the number of times the function is called
		//the time resets after each function call
		void add_function(Empaerior::ECS& ecs, const Empaerior::u_inter& id, const Empaerior::u_inter& time, Timed_Function function, const Empaerior::s_inter call_number = -1)
		{
			//adds the necessary data in the containers
			ecs.get_component<T_E_Component>(id).time.emplace_back(time);
			ecs.get_component<T_E_Component>(id).functions.emplace_back(function);
			ecs.get_component<T_E_Component>(id).elapsed_time.emplace_back(0);
			ecs.get_component<T_E_Component>(id).call_times.emplace_back(call_number);
		}

	//iterates throught the container and executes the functions for which enough time has passed
#define component ecs.get_component<T_E_Component>(id)
		void Update(Empaerior::ECS& ecs, const Empaerior::u_int& dt)
		{
			for (auto& id : entityList->entities_id)
			{
				for (Empaerior::u_inter i = 0; i < component.functions.size(); i++)
				{
					component.elapsed_time[i] += dt;
					//if enought time has passed,execute the function and delete it from the registry
					if (component.elapsed_time[i] >= component.time[i])
					{
							//call function
							component.functions[i]();

							//if the function has been called *call_time* times
							if (component.call_times[i]  == 1)
							{
								//erase all
								component.elapsed_time.erase(component.elapsed_time.begin() + i);
								component.time.erase(component.time.begin() + i);
								component.functions.erase(component.functions.begin() + i);
							}
							else if (component.call_times[i] > 1)
							{
								--component.call_times[i] ;
							}
						

					}

				}

			}

		}
#undef component
	public:
		std::shared_ptr<Empaerior::EntitySystemList> entityList;


	};

	class singleSpriteSystem 
	{
	public:

		void Init(Empaerior::ECS& ecs , VK_Renderer* p_renderer,Empaerior::Scene2D* p_scene)
		{
			if(!ecs.is_component_registered<Empaerior::singleSprite_Component>() )ecs.register_component<Empaerior::singleSprite_Component>();
			ecs.add_criteria_for_iteration<Empaerior::singleSpriteSystem, Empaerior::singleSprite_Component>();	
			renderer = p_renderer;
			scene = p_scene;
			scene->init(*renderer);
		}
		
        //default createSprite
		void createSprite(Empaerior::ECS& ecs,
			const Empaerior::u_inter& id,
			const Empaerior::Float_Rect_S& rect,
			const Empaerior::Float_Rect_S& texRect,
			const uint32_t textureID
		)
		{
			Empaerior::createSprite(scene->geometrybuffer, renderer->texture_atlas, ecs.get_component<Empaerior::singleSprite_Component>(id).sprites, rect, texRect, textureID);
		}

#pragma  region createSpritesOverloads
        //create sprite but use the whole texture
        void createSprite(Empaerior::ECS& ecs,
                          const Empaerior::u_inter& id,
                          const Empaerior::Float_Rect_S& rect,
                          const uint32_t textureID
        )
        {
            Empaerior::createSprite(scene->geometrybuffer, renderer->texture_atlas, ecs.get_component<Empaerior::singleSprite_Component>(id).sprites, rect,
                                    {0,0,renderer->texture_atlas.image_dimensions[textureID][0],renderer->texture_atlas.image_dimensions[textureID][1]}, textureID);
        }
        //string to image instead of texID
        void createSprite(Empaerior::ECS& ecs,
                          const Empaerior::u_inter& id,
                          const Empaerior::Float_Rect_S& rect,
                          const Empaerior::Float_Rect_S& texRect,
                          const std::string& texturePath
        )
        {
            Empaerior::createSprite(scene->geometrybuffer, renderer->texture_atlas, ecs.get_component<Empaerior::singleSprite_Component>(id).sprites, rect, texRect, renderer->texture_atlas.create_texture_from_file(texturePath));
        }
        //create sprite but use the whole texture and use string instead of textureID
        void createSprite(Empaerior::ECS& ecs,
                          const Empaerior::u_inter& id,
                          const Empaerior::Float_Rect_S& rect,
                          const std::string& texturePath
        )
        {
		    size_t texID =  renderer->texture_atlas.create_texture_from_file(texturePath);
            Empaerior::createSprite(scene->geometrybuffer, renderer->texture_atlas, ecs.get_component<Empaerior::singleSprite_Component>(id).sprites, rect,
                                    {0,0,renderer->texture_atlas.image_dimensions[texID][0],renderer->texture_atlas.image_dimensions[texID][1]},texID);
        }

#pragma endregion
		void destroySprite(Empaerior::ECS* ecs, const Empaerior::u_inter& entity_id) 
		{
			Empaerior::destroySprite(ecs->get_component<singleSprite_Component>(entity_id).sprites);
		}
		

	private:
		VK_Renderer* renderer;
		Empaerior::Scene2D* scene;
	public:
		std::shared_ptr<Empaerior::EntitySystemList> entityList;

	};
}
