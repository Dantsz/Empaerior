#pragma once
#include "../../include/core/defines/defines.h"

#include "../rendering/vulkan_rendering/camera.h"
#include "../rendering/vulkan_rendering/graphic_settings.h"
namespace Empaerior
{
	namespace Input
	{
		namespace Mouse
		{
			//returns the coordinates of the mouse relative to the screen
			Empaerior::Point2f get_screen_mouse_coords(const Empaerior::VK_RendererGraphicsInfo& renderSettings);
			
			//gets the coordinates of the mouse based on where the camera is
			Empaerior::Point2f get_world_mouse_coords(const Empaerior::VK_RendererGraphicsInfo& renderSettings,const Empaerior::Camera2D& camera);
			
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