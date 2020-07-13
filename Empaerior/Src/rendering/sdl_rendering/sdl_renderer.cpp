#include "sdl_renderer.h"
#include "../window.h"

static inline SDL_Renderer* sdl_renderer = nullptr;
namespace Empaerior::SDL_Rendering
{

	void attach_window(Empaerior::Window& window)
	{
		sdl_renderer = SDL_CreateRenderer(window.window, -1, SDL_WINDOW_OPENGL);
	}

	void set_render_dimensions(Empaerior::u_int width, Empaerior::u_int height)
	{
		SDL_RenderSetLogicalSize(sdl_renderer, width, height);
	}

	void render()
	{
		SDL_RenderPresent(sdl_renderer);
	}

	void clear()
	{
		SDL_RenderClear(sdl_renderer);
	}

	SDL_Renderer* get_renderer()
	{
		return sdl_renderer;
	}




}
