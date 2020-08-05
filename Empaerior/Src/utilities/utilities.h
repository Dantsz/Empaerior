#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

#include <cmath>
#include "../include/core/defines/defines.h"

namespace Empaerior
{
	namespace Utilities {
		//clipboard functions



		 Empaerior::string get_clipboard_text();

		 void set_clipboard_text(const char* text);




		//system functions
		 EMP_FORCEINLINE Empaerior::string get_platform()//gets the current platform
		{
			const char* sdl_platform = SDL_GetPlatform();
			Empaerior::string e_platform = sdl_platform;
			SDL_free((void*)sdl_platform);
			return e_platform;

		}

		 EMP_FORCEINLINE int cpu_cache_size()// returns the size of the cpu  cache in bytes
		{
			return SDL_GetCPUCacheLineSize();
		}
		
		 EMP_FORCEINLINE int get_core_number()// get the number of CPU cores available
		{
			return SDL_GetCPUCount();
		}
		 EMP_FORCEINLINE int get_system_ram()//get the amount of RAM configured in the system.
		{
			return SDL_GetSystemRAM();
		}

		EMP_FORCEINLINE std::string get_date_string()
		{
			 auto t = std::time(nullptr);
			 auto tm = *std::localtime(&t);

			 std::ostringstream oss;
			 oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
			 return  oss.str();

		 }

		//check if a rect contains a point
		Empaerior::boole rect_contains_point(const Empaerior::Float_Rect& rect, Empaerior::fl_point x , Empaerior::fl_point y);
		Empaerior::boole rect_contains_point(const Empaerior::Float_Rect& rect,const Empaerior::Point2f point);
		//rotate point around axis
		Empaerior::Point2f get_rotated_point(const Empaerior::Point2f& point, const Empaerior::Point2f& axis, const Empaerior::fl_point angle);

		//takes a screenshot
		void take_screenshot(Empaerior::Window& window, std::string name = get_date_string());




	}

	



}