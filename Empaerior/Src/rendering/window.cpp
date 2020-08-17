#include "pch.h"
#include "../rendering/window.h"
#include "../include/application.h"


Empaerior::Window::Window(const Empaerior::string& name, const Empaerior::u_int& width, const Empaerior::u_int& height)
{
	
	Init(name, width, height);
}

Empaerior::Window::Window()
{

}

int Empaerior::Window::Init(const Empaerior::string& name, const Empaerior::u_int& m_width, const Empaerior::u_int& m_height)
{
	width = m_width;
	height = m_height;
	window = SDL_CreateWindow(name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
	

	//SDL_RendererInfo info;
	//SDL_GetRendererInfo(Empaerior::Application::window.renderer, &info);
	//information.render_API = info.name;



	window_listener.register_event(SDL_QUIT, [](Empaerior::Event const& event) { // add quit event 
		Empaerior::Application::is_running = false;
		});

	window_listener.register_event(SDL_WINDOWEVENT, [window = this](Empaerior::Event const& event) { //add 
		switch (event.event.window.event) {
		case SDL_WINDOWEVENT_MINIMIZED:
			Empaerior::Application::is_paused = true;
			break;

		case SDL_WINDOWEVENT_RESTORED || SDL_WINDOW_MAXIMIZED:
			Empaerior::Application::is_paused = false;
			break;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_GetWindowSize(window->window , &window->width, &window->height);
		break;


		}
	
		});

	return 0;
}

void Empaerior::Window::render()
{

}

void Empaerior::Window::clear()
{
}


void Empaerior::Window::reset()
{
	if (window != nullptr)	SDL_DestroyWindow(window);
	
}
