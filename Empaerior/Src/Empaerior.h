#pragma once


#include "application.h"
#include "state/state.h"


#include <SDL.h>

#include <SDL_mixer.h>

#include "../Include/core/core.h"

#include "../Include/assetmanager/assetmanager.h"

#include "rendering/sdl_rendering/sdl_renderer.h"


#include "systems/systems.h"
#include "systems/component.h"

#include "rendering/window.h"
#include "rendering/camera.h"
#include "rendering/sdl_rendering/objects/sprite.h"





#include "input/input.h"



#ifdef emp_use_logs

#include "debugging/log.h"
#include "debugging/get_data_info.h"
	
#endif