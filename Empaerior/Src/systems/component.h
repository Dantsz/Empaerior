#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "rendering/camera.h"
#include "rendering/sdl_rendering/objects/sprite.h"
#include "../include/core/defines/defines.h"
#include "input/eventhandler/eventhandler.h"

namespace Empaerior
{


	
	/*
	New Sprite Component
	*/
	

	
	struct Animation
	{

		Empaerior::Int_Rect rect;//the frame of the animation
		Empaerior::u_inter next_animation; // the next animation in line, as index in animations
	};

	


	struct Sprite_Component
	{
		
		Empaerior::vector<Empaerior::u_inter> sprite_indexes;

		struct Animation_Entry
		{
			Empaerior::u_inter anim_begin;
			Empaerior::u_inter anim_end;
		};

		Empaerior::unsafe_vector<Animation_Entry> animation_index;

	
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