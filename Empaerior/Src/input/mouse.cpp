#include "pch.h"
#include "mouse.h" 
#include "application.h"

Empaerior::Point2f Empaerior::Input::Mouse::get_screen_mouse_coords(Empaerior::fl_point viewportX , Empaerior::fl_point	 viewportY, Empaerior::fl_point viewportW, Empaerior::fl_point viewportH)
{

	//get the positions
	Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> pos;
	Empaerior::Point2f f_pos;


	SDL_GetMouseState(&pos.first, &pos.second);



	f_pos[0] = float(pos.first);
	f_pos[1] = float(pos.second);



	//Scale down the positions to match the windows
	int width, height;
	SDL_GetWindowSize(Empaerior::Application::window.window, &width, &height);

	float sx = static_cast<float>(width);
	float sy = static_cast<float>(height);
	f_pos[0] /= sx;
	f_pos[1] /= sy;

	f_pos[0] *= viewportW;
	f_pos[1] *= viewportH;




	





	return f_pos;
}

Empaerior::Point2f Empaerior::Input::Mouse::get_world_mouse_coords(Empaerior::fl_point viewportX, Empaerior::fl_point	 viewportY, Empaerior::fl_point viewportW, Empaerior::fl_point viewportH,const Empaerior::Camera2D& camera)
{
	
		//get the positions
		Empaerior::v_pair<Empaerior::s_int, Empaerior::s_int> pos;
		Empaerior::Point2f f_pos;


		SDL_GetMouseState(&pos.first, &pos.second);



		f_pos[0] = float(pos.first);
		f_pos[1] = float(pos.second);



		//Scale down the positions to match the world
		int width, height;
		SDL_GetWindowSize(Empaerior::Application::window.window, &width, &height);

		float sx = static_cast<float>(width);
		float sy = static_cast<float>(height);
		f_pos[0] /= sx;
		f_pos[1] /= sy;

		f_pos[0] *= viewportW;
		f_pos[1] *= viewportH;

		f_pos[0] += camera.position.x;
		f_pos[1] += camera.position.y;

		f_pos[0] /= camera.scale;
		f_pos[1] /= camera.scale;
	
		Empaerior::Int_Rect renderer_viewport;





		return f_pos;

	
}
