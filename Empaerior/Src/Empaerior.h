#pragma once


#include "application.h"
#include "state/state.h"


#include <SDL.h>

#include <SDL_mixer.h>

#include "../include/core/core.h"

#include "../include/assetmanager/assetmanager.h"

#include "rendering/sdl_rendering/sdl_renderer.h"


#include "systems/systems.h"
#include "systems/component.h"

#include "../include/rendering/window.h"
#include "../include/rendering/camera.h"
#include "rendering/sdl_rendering/objects/sprite.h"





#include "../include/input/input.h"



#ifdef emp_use_logs

#include "debugging/log.h"
#include "debugging/get_data_info.h"
	
#endif