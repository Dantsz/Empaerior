#pragma once
#include "../core/defines/defines.h"
#include "../rendering/camera.h"
namespace Empaerior
{
	namespace Input
	{
		namespace Mouse
		{
			//returns the coordinates of the mouse relative to the screen
			Empaerior::Point2f get_screen_mouse_coords();
			
			//gets the coordinates of the mouse based on where the camera is
			Empaerior::Point2f get_world_mouse_coords(const Empaerior::Camera& camera);
			
			//Toggle the cursor
			//0 - no
			//1 - yes
			EMP_FORCEINLINE void show_cursor(Empaerior::boole toogle)
			{
				SDL_ShowCursor(toogle);
			}


		}
	}
};