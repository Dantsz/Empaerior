#pragma once

#include "../include/input/eventhandler/eventhandler.h"
#include "../include/core/defines/defines.h"
namespace Empaerior
{
	struct Window_Info
	{
		Empaerior::string render_API;
	};

	class Window
	{
		friend class Application;

	public:
		Window();
		Window(const Empaerior::string& name, const Empaerior::u_int& width, const Empaerior::u_int& height);




		~Window()
		{
			if (window != nullptr)	SDL_DestroyWindow(window);
			

		}
		int Init(const Empaerior::string& name, const Empaerior::u_int& width, const Empaerior::u_int& height);
		void render();
		void clear();

		void reset();
		

		EMP_FORCEINLINE Empaerior::u_int get_width()
		{
			return width;
		}

		EMP_FORCEINLINE Empaerior::u_int get_heigth()
		{
			return height;
		}


		


		SDL_Window* window;
		//lisens for window events
		Event_Listener window_listener;

		Window_Info information;
	
		Empaerior::u_int width = 0;
		Empaerior::u_int height = 0;
	};


	namespace Window_Functions
	{
	


		//Changes the name of the window
		EMP_FORCEINLINE void change_window_name(const Empaerior::Window& window,const Empaerior::string& new_name)
		{
			SDL_SetWindowTitle(window.window, new_name.c_str());
		}

		//Toggles fullscreen
		EMP_FORCEINLINE void toggle_fullscreen(const Empaerior::Window& window)
		{
			Empaerior::u_int FullscreenFlag = SDL_WINDOW_FULLSCREEN;
			bool IsFullscreen = SDL_GetWindowFlags(window.window) & FullscreenFlag;
			SDL_SetWindowFullscreen(window.window, IsFullscreen ? 0 : FullscreenFlag);
		}

		//TODO : ADD SET ICON FUNCTION


	}


}