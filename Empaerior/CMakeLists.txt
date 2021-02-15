project(Empaerior CXX)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "src/application.cpp"
    "include/application.h"
    "include/Empaerior.h"
    "include/EmpaeriorEngine.h"
    "src/pch.cpp"
    "src/pch.h"
)
source_group("" FILES ${no_group_source_files})

include("include/core/CMakeLists.txt")



set(input
	"include/input/input.h"
	"include/input/keyboard.h"
	"include/input/mouse.h"
	"src/input/mouse.cpp"
)

source_group("input" FILES ${input})

set(input__eventhandler
    "src/input/eventhandler/eventhandler.cpp"
    "include/input/eventhandler/eventhandler.h"
		
)
source_group("input\\eventhandler" FILES ${input__eventhandler})

set(rendering

    "src/rendering/window.cpp"
    "include/rendering/window.h"
)
source_group("rendering" FILES ${rendering})



#include("src/rendering/sdl_rendering/CMakeLists.txt")

include ("include/rendering/vulkan_rendering/CMakeLists.txt")

set(state
    "src/state/state.cpp"
    "include/state/state.h"
)
source_group("state" FILES ${state})

set(systems
    "include/systems/component.h"
    "include/systems/systems.h"
	"src/systems/systems.cpp"
)
source_group("systems" FILES ${systems})

set (debugging 
	"include/debugging/get_data_info.h"

)
source_group("debugging" FILES ${debugging})


set ( utilities
	"include/utilities/utilities.h"
	"src/utilities/utilities.cpp"
	)
source_group("utilities" FILES ${utilities})
		
set(SDLwrappers
	"include/SDLwrappers/sdl_wrappers.h"
)
source_group("SDLwrapper" FILES ${SDLwrappers})
set(ALL_FILES

	${core_all_files}
    ${no_group_source_files}
    ${input}
    ${input__eventhandler}
    ${rendering}
	${vulkan_rendering}
    ${state}
    ${systems}
	${debugging}
	${utilities}
	${SDLwrappers}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})


set(ROOT_NAMESPACE Empaerior)

################################################################################
# Target name
################################################################################

    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "Empaerior"
        TARGET_NAME_DIST    "Empaerior"
        TARGET_NAME_RELEASE "Empaerior"
    )

################################################################################
# Output directory
################################################################################
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug64-windows-/Empaerior/"
        OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist64-windows-/Empaerior/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release64-windows-/Empaerior/"
		
		
    )

################################################################################
# Include directories
################################################################################

    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_mixer/include;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/stb;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/glm;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanSDK/include;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanMemoryAllocator/src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/spdlog/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/freetype/include"
    )


