#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>


#include "../include/core/defines/defines.h"
#include "../include/input/eventhandler/eventhandler.h"
#include "../include/rendering/vulkan_rendering/sprite.h"

namespace Empaerior
{


	
	/*
	New Sprite Component
	*/
	


	//holds only one sprite
	struct singleSprite_Component
	{	
		Empaerior::Sprite sprites;
	};


	struct Event_Listener_Component
	{ 
		Event_Listener event_listener;
	};


	//Timed Exceution Component
	struct T_E_Component
	{
		//the function
		using Timed_Function = std::function<void()>;
		//times passes
		Empaerior::vector<Empaerior::u_inter> elapsed_time;
		//the total time
		Empaerior::vector<Empaerior::u_inter> time;
		//function container	
		Empaerior::vector<Timed_Function> functions;
		//the times the functions is to be called
		Empaerior::vector<Empaerior::s_inter> call_times;
	};


}