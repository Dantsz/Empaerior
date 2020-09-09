//just a edited version of the imgui sdl implementation
#pragma once
#include "../imgui-master/imgui.h"

// SDL
#include <SDL.h>

#ifdef _WIN32
#include <SDL_syswm.h>
#endif	


#if defined(__APPLE__)
#include "TargetConditionals.h"
#endif

#include <Empaerior.h>
namespace ImGuiEmpImpl
{
	bool Init(const Empaerior::Window& window);
	void NewFrame(const Empaerior::Window& window );
	bool ProcessEvent(const Empaerior::Event& event);
	void Shutdown();
}