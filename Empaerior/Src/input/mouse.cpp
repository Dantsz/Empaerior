#include "pch.h"
#include "mouse.h" 
#include "application.h"
Empaerior::Point2f Empaerior::Input::Mouse::get_screen_mouse_coords()
{

	//Transform for the position of the renderer
	//This is in case the viewport  doesn't match the camera (blackboxing)

	//get the positions
	Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> pos;
	Empaerior::Point2f f_pos;


	SDL_GetMouseState(&pos.first, &pos.second);



	f_pos.x = float(pos.first);
	f_pos.y = float(pos.second);



	//Scale down the positions to match the world
	float sx = 0;
	float sy = 0;
	SDL_RenderGetScale(Application::window.renderer, &sx, &sy);

	f_pos.x /= sx;
	f_pos.y /= sy;




	//Transform for the position of the renderer
	Empaerior::Int_Rect renderer_viewport;

	SDL_RenderGetViewport(Application::window.renderer, &renderer_viewport);
	f_pos.x -= renderer_viewport.x;
	f_pos.y -= renderer_viewport.y;


	f_pos.x /= renderer_viewport.w;
	f_pos.y /= renderer_viewport.h;


	return f_pos;
}

Empaerior::Point2f Empaerior::Input::Mouse::get_world_mouse_coords(const Empaerior::Camera& camera)
{
	{
		//get the positions
		Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> pos;
		Empaerior::Point2f f_pos;


		SDL_GetMouseState(&pos.first, &pos.second);



		f_pos.x = float(pos.first);
		f_pos.y = float(pos.second);



		//Scale down the positions to match the world
		float sx = 0;
		float sy = 0;
		SDL_RenderGetScale(Empaerior::Application::window.renderer, &sx, &sy);

		f_pos.x /= sx;
		f_pos.y /= sy;




		//Transform for the position of the renderer
		Empaerior::Int_Rect renderer_viewport;

		SDL_RenderGetViewport(Empaerior::Application::window.renderer, &renderer_viewport);
		f_pos.x -= renderer_viewport.x;
		f_pos.y -= renderer_viewport.y;

		//Transform the position relative to the camera dimesnions
		f_pos.x *= camera.rect.w;
		f_pos.y *= camera.rect.h;



		f_pos.x /= renderer_viewport.w;
		f_pos.y /= renderer_viewport.h;



		//Tranform for position
		f_pos.x += camera.rect.x;
		f_pos.y += camera.rect.y;




		return f_pos;

	}
}
