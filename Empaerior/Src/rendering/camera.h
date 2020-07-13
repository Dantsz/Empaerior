#pragma once
#include <SDL.h>
#include "core/defines/defines.h"
#include "rendering/sdl_rendering/sdlwrappers/rendering_wrappers.h"
namespace Empaerior
{

	class Camera
	{
	public:
		Camera()
		{

		}
		~Camera()
		{

		}
		Camera(const Empaerior::Int_Rect& camera)
			:rect(camera)

		{

		}
		Camera(const Empaerior::s_int& x, const Empaerior::s_int& y, const Empaerior::s_int& w, const Empaerior::s_int& h)
			:rect({ x,y,w,h })

		{

		}
		void set_position(const Empaerior::s_int& x, const Empaerior::s_int& y)
		{
			rect.x = x;
			rect.y = y;

		}
		void set_dimensions(const  Empaerior::s_int& w, const  Empaerior::s_int& h);


		Empaerior::Int_Rect rect = { 0,0,0,0 };
	private:


	};
}