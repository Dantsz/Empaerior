#pragma once
#include <SDL.h>
#include "../include/core/defines/defines.h"


namespace Empaerior
{
	using Int_Rect = SDL_Rect;

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