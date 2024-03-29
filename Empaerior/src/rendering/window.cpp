#include "SDL_error.h"
#include "SDL_vulkan.h"
#include "core/defines/basic_defines.h"
#include "pch.h"
#include "../include/rendering/window.h"
#include "../include/application.h"


Empaerior::Window::Window(const Empaerior::string& name, const Empaerior::s_int& windowWidth, const Empaerior::s_int& windowHeight)
{
	
	Init(name, windowWidth, windowHeight);
}

Empaerior::Window::Window() = default;

int Empaerior::Window::Init(const Empaerior::string& name, const Empaerior::s_int& m_width, const Empaerior::s_int& m_height)
{
	width = m_width;
	height = m_height;
	window = SDL_CreateWindow(name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
	if(window == nullptr) 
	{
		Empaerior::log(SDL_GetError());
	}

	window_listener.register_event(SDL_QUIT, [](Empaerior::Event& event) { // add quit event 
		Empaerior::Application::is_running = false;
		event.is_handled = true;
		});

	window_listener.register_event(SDL_WINDOWEVENT, [window = this](Empaerior::Event const& event) { //add 
		switch (event.event.window.event) {
		case SDL_WINDOWEVENT_MINIMIZED:
			Empaerior::Application::is_paused = true;
			break;
		case (SDL_WINDOWEVENT_RESTORED):
			Empaerior::Application::is_paused = false;
			break;
		case (SDL_WINDOW_MAXIMIZED):
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


std::vector<const char*> Empaerior::Window::getVulkanRequiredInstanceExtensions()
{
	std::vector<const char*> extensions{};

    uint32_t count = 0;
    SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr);
    // now count is (probably) 2.
    extensions.resize(count);
    // now call again with that not-NULL array you just allocated.
    SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data());

	return extensions;
}



void Empaerior::Window::reset() const
{
	if (window != nullptr)	SDL_DestroyWindow(window);
	
}
