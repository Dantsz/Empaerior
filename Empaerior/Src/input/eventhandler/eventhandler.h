#pragma once
#include <SDL.h>
#include<SDL_events.h>
#include <functional>
#include "../include/core/defines/defines.h"

namespace Empaerior {


	struct Event
	{
		//the event
		SDL_Event event;
		//Check to see if it was handled
		Empaerior::boole is_handled = false;
	};

	//make an event handled
	void event_handled(Empaerior::Event& event);
	//check if is handled
	Empaerior::boole is_event_handled(const Empaerior::Event& event);

	//stack overflow to the rescue
	class Event_Listener
	{
	public:

		using EventCallback = std::function<void(Empaerior::Event&)>;

		Event_Listener() {};
		~Event_Listener() {};


		void register_event(Empaerior::u_int type, EventCallback callback,Empaerior::s_inter call_times =-1); //put a callback in the lisener
		
		void handleEvents(Empaerior::Event& cur_event); //execute commands
		

		Empaerior::hash_map<Empaerior::u_inter , Empaerior::vector<Empaerior::v_pair<EventCallback,Empaerior::s_inter>>> _registeredCallbacks;//type of the event and function
	};
}

