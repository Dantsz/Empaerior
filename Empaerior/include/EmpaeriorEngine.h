#pragma once

//#include "pch.h"

#include "Empaerior.h"


#include "../include/core/exceptions/exceptions.h"
#include "application.h"
#include "debugging/log.h"
#include "utilities/utilities.h"
#include  "../include/core/utilities/timer.h"
#include "SDLwrappers/sdl_wrappers.h"



//static objects variables
#pragma region static objects


#pragma region app_statics
Empaerior::vector <Empaerior::State*> Empaerior::Application::states;
Empaerior::vector <Empaerior::u_inter> Empaerior::Application::active_states;
Empaerior::vector <Empaerior::u_inter> Empaerior::Application::to_be_paused;
Empaerior::vector <Empaerior::u_inter> Empaerior::Application::to_be_deleted;
Empaerior::vector <Empaerior::u_inter> Empaerior::Application::freed_indexes;
//time between frames
Empaerior::u_int Empaerior::Application::dt = 1000 / 60;
Empaerior::boole Empaerior::Application::is_paused = false;
Empaerior::boole Empaerior::Application::is_running = true;
Empaerior::Event Empaerior::Application::event;
Empaerior::Window Empaerior::Application::window;

#pragma endregion

#pragma endregion


extern Empaerior::Application* Empaerior::Create_Application();
//THIS IS THE ENTRY POINT 

//#define SDL_MAIN_HANDLED
inline int main(int argc, char** argv)
{

#ifdef EMP_USE_LOGS

	
 
#endif // EMPAERIOR_DEBUG

	#pragma region SDL_Inititalization

	try {

#ifdef EMP_USE_LOGS
		Empaerior::log("INITIALIZING SDL");
#endif // EMPAERIOR_DEBUG
		uint16_t error_flags = SDLW::Init();
		//check for errors
		if(error_flags & SDLW::sdl)
		{
			throw E_runtime_exception("Failed to initialize SDL", __FILE__, __LINE__, __FUNCTION__);
		}
		if (error_flags & SDLW::sdl_image)
		{
			throw E_runtime_exception("Failed to initialize SDL Graphics", __FILE__, __LINE__, __FUNCTION__);
		}
		if (error_flags & SDLW::sdl_ttf)
		{
			throw E_runtime_exception("Failed to initialize SDL Font", __FILE__, __LINE__, __FUNCTION__);
		}
		if (error_flags & SDLW::sdl_mix)
		{
			throw E_runtime_exception("Failed to initialize SDL Audio", __FILE__, __LINE__, __FUNCTION__);
		}

	}
	catch (E_runtime_exception & e)
	{
		e.print_message();
	}
	
	
	#pragma endregion




	
	
	
#ifdef EMP_USE_LOGS
	Empaerior::Timer timer;
	timer.start();

	Empaerior::log("Creating Application");
#endif // EMPAERIOR_DEBUG
	Empaerior::Application* application = Empaerior::Create_Application();
	
	application->Init();
	
	
	try {
		
#ifdef EMP_USE_LOGS
		Empaerior::log("Runnning Aplication");
#endif // EMPAERIOR_DEBUG
		application->run();

	}
	catch (std::runtime_error & e)
	{

		Empaerior::log(e.what());
        //throw e;
	}
	


#ifdef EMP_USE_LOGS
	Empaerior::log("Stoping Application");
	
	Empaerior::log("Application ran for " +std::to_string(timer.getTicks()) + " ms");
	timer.stop();
#endif // EMPAERIOR_DEBUG

	Empaerior::Application::clear_states();
	Empaerior::Application::window.reset();



	SDLW::Quit();


	return 0;


}