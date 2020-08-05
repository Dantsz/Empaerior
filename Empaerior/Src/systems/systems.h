#pragma once

#include "../include/core/exceptions/exceptions.h"


#include "../include/core/ecs/ecs.h"

#include "component.h"
#include "rendering/sdl_rendering/objects/sprite.h"

#include "input/eventhandler/eventhandler.h"
#include "rendering/sdl_rendering/sdlwrappers/rendering_wrappers.h"

#include <set>

namespace Empaerior
{
	class Event_System : public Empaerior::System
	{
	public:

		~Event_System()
		{

		}

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
			std::vector<Empaerior::u_inter>::reverse_iterator Iterator = entities_id.rbegin();
			//ITERATING THROUGH THE ENTITIES IN REVERSE
			while (Iterator != entities_id.rend() && !Empaerior::is_event_handled(event))
			{
				EVENTLISTENER.handleEvents(event);
				Iterator++;
			}
			
			
			
			
#undef EVENTLISTENER

		}



	};

	

	

	class T_E_System : public Empaerior::System
	{
	public:

		~T_E_System()
		{

		}

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
			for (auto& id : entities_id)
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


	};

}