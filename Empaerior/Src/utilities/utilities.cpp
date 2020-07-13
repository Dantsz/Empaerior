#include "pch.h"
#include "utilities.h"
#include "core/utilities/math.h"


Empaerior::string Empaerior::Utilities::get_clipboard_text()
{
	if (SDL_HasClipboardText())//if there's text
	{
		char* sdl_text = SDL_GetClipboardText();//get the clipboard content as char*
		Empaerior::string clip_text = sdl_text;//transfom  the char* into a Empaerior::string
		SDL_free(sdl_text);//free the char*
		return clip_text;//return a string
	}
	return "";
}

void Empaerior::Utilities::set_clipboard_text(const char* text)
{
	try
	{
		if (SDL_SetClipboardText(text) < 0)
		{
			throw E_runtime_exception("Cannot copy text to clipboard", __FILE__, __LINE__, __FUNCTION__);
		}
	}
	catch (E_runtime_exception & e) {

		e.print_message();
		return;
	}
}




Empaerior::boole Empaerior::Utilities::rect_contains_point(const Empaerior::Float_Rect& rect, Empaerior::fl_point x, Empaerior::fl_point y)
{

	Empaerior::fl_point o_x = rect.dimensions.x + rect.dimensions.w/2;
	Empaerior::fl_point o_y = rect.dimensions.y + rect.dimensions.h/2;


	//rotating the point counter-clockwise
	Empaerior::fl_point c_x = o_x +  (x - o_x) * Empaerior::Math::cosd(rect.angle) - (y - o_y) * Empaerior::Math::sind(rect.angle);
	Empaerior::fl_point c_y = o_y +	(y - o_y) * Empaerior::Math::cosd(rect.angle) + (x - o_x) * Empaerior::Math::sind(rect.angle);
	
	//
	

	
	//checking the collision
	if (c_x <= rect.dimensions.x || c_x > rect.dimensions.x + rect.dimensions.w) return false;
	if (c_y <= rect.dimensions.y || c_y > rect.dimensions.y + rect.dimensions.h) return false;

	return true;
}

Empaerior::boole Empaerior::Utilities::rect_contains_point(const Empaerior::Float_Rect& rect, const Empaerior::Point2f point)
{


	Empaerior::fl_point o_x = rect.dimensions.x + rect.dimensions.w / 2;
	Empaerior::fl_point o_y = rect.dimensions.y + rect.dimensions.h / 2;



	//rotating the point counter-clockwise
	Empaerior::fl_point c_x = o_x + (point[0] - o_x) * Empaerior::Math::cosd(rect.angle) - (point[1] - o_y) * Empaerior::Math::sind(rect.angle);
	Empaerior::fl_point c_y = o_y + (point[1] - o_y) * Empaerior::Math::cosd(rect.angle) + (point[0] - o_x) * Empaerior::Math::sind(rect.angle);

	//



	//checking the collision
	if (c_x <= rect.dimensions.x || c_x > rect.dimensions.x + rect.dimensions.w) return false;
	if (c_y <= rect.dimensions.y || c_y > rect.dimensions.y + rect.dimensions.h) return false;

	return true;
}




void Empaerior::Utilities::take_screenshot(Empaerior::Window& window, std::string name )
{
	SDL_Surface* sshot = SDL_CreateRGBSurface(0, window.get_width() , window.get_heigth(), 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(Empaerior::SDL_Rendering::get_renderer(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
	name += ".bmp";
	SDL_SaveBMP(sshot,name.c_str());
	SDL_FreeSurface(sshot);
}

