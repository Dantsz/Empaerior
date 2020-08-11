project(Empaerior CXX)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "Src/application.cpp"
    "Src/application.h"
    "Src/Empaerior.h"
    "Src/main.h"
    "Src/pch.cpp"
    "Src/pch.h"
)
source_group("" FILES ${no_group_source_files})

include("include/core/CMakeLists.txt")

set(assetmanager
    "Src/assetmanager/assetmanager.cpp"
    "include/assetmanager/assetmanager.h"
)
source_group("assetmanager" FILES ${assetmanager})

set(input
	"include/input/input.h"
	"include/input/keyboard.h"
	"include/input/mouse.h"
	"Src/input/mouse.cpp"
)

source_group("input" FILES ${input})

set(input__eventhandler
    "Src/input/eventhandler/eventhandler.cpp"
    "include/input/eventhandler/eventhandler.h"
		
)
source_group("input\\eventhandler" FILES ${input__eventhandler})

set(rendering
    "Src/rendering/camera.cpp"
    "include/rendering/camera.h"
    "Src/rendering/window.cpp"
    "include/rendering/window.h"
)
source_group("rendering" FILES ${rendering})



#include("Src/rendering/sdl_rendering/CMakeLists.txt")

include ("include/rendering/vulkan_rendering/CMakeLists.txt")

set(state
    "Src/state/state.cpp"
    "include/state/state.h"
)
source_group("state" FILES ${state})

set(systems
    "Src/systems/component.h"
    "Src/systems/systems.h"
	"Src/systems/systems.cpp"
)
source_group("systems" FILES ${systems})

set (debugging 
	"include/debugging/get_data_info.h"
    "Src/debugging/log.cpp"
    "include/debugging/log.h"
)
source_group("debugging" FILES ${debugging})


set ( utilities
	"Src/utilities/utilities.h"
	"Src/utilities/utilities.cpp"
	)
source_group("utilities" FILES ${utilities})


set(ALL_FILES

	${core_all_files}
    ${no_group_source_files}
    ${assetmanager}
    ${input}
    ${input__eventhandler}
    ${rendering}
    ${sdl_rendering}
	${vulkan_rendering}
    ${state}
    ${systems}
	${debugging}
	${utilities}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Empaerior)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
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
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug32-windows-/Empaerior/"
        OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist32-windows-/Empaerior/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release32-windows-/Empaerior/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug64-windows-/Empaerior/"
        OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist64-windows-/Empaerior/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release64-windows-/Empaerior/"
		
		
    )
endif()
################################################################################
# Include directories
################################################################################

    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_mixer/include;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/stb;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/glm;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanSDK/include;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanMemoryAllocator/src;"
        	"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/spdlog/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/freetype/include"
    )


################################################################################
# Compile definitions
################################################################################

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "EMPAERIOR_DEBUG"
        ">"
        "$<$<CONFIG:Dist>:"
            "EMPAERIOR_DIST"
        ">"
        "$<$<CONFIG:Release>:"
            "EMPAERIOR_RELEASE"
        ">"
        "_CRT_SECURE_NO_WARNINGS;"
        "EMPAERIOR_WINDOWS;"
        "UNICODE;"
        "_UNICODE"
    )


################################################################################
# Compile and link options
################################################################################
if(MSVC)
 
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /MD;
                /ZI
            >
            $<$<CONFIG:Dist>:
                /Gm-;
                /Ox;
                /Oi;
                /GF;
                /MD;
                /Gy;
				/Ot;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
                /Gm-;
                /Ox;
                /Oi;
                /GF;
                /MD;
                /Gy;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
   
    
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Dist>:
                /OPT:REF;
                /OPT:ICF
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:WINDOWS
        )
   
endif()