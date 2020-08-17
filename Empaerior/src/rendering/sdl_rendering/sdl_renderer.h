#pragma once
#include "glyphs/glyphs.h"
#include "sdlwrappers/ptr_wrappers.h"
#include "sdlwrappers/rendering_wrappers.h"
#include "sdlwrappers/sdl_wrappers.h"
#include "../../../include/rendering/window.h"


namespace Empaerior::SDL_Rendering
{

	void attach_window(Empaerior::Window& window);
	void set_render_dimensions(Empaerior::u_int width, Empaerior::u_int height);
	void render();
	void clear();
	SDL_Renderer* get_renderer();

}