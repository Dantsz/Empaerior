project(Application CXX)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "Src/Application.cpp"
)

source_group("" FILES ${no_group_source_files})

#Add the main cpp
set(ALL_FILES ${no_group_source_files})

#Include Tools 
include("Src/Tools/CMakeLists.txt")




################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Application)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################

    set_target_properties(${PROJECT_NAME} PROPERTIES
	
        TARGET_NAME_DEBUG   "Application"
        TARGET_NAME_DIST    "Application"
        TARGET_NAME_RELEASE "Application"
    )

################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")

	set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug32/Application/"
        OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist32/Application/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release32/Application/"
		)

elseif ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
	
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug64/Application/"
        OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist64/Application/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release64/Application/"
    )
endif()

################################################################################
# Include directories
################################################################################

    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2/include;"
       
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_mixer/include;"
        
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/spdlog/include;"
		
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/stb;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/glm;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanSDK/Include;"
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanMemoryAllocator/src;"
			
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/freetype/include"
		
        
		"${CMAKE_CURRENT_SOURCE_DIR}/../Empaerior/include"
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
            $<$<CONFIG:Debug>:
                /DEBUG;
                /INCREMENTAL
            >
            $<$<CONFIG:Dist>:
                /DEBUG:FULL;
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:Release>:
                /DEBUG:FULL;
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /SUBSYSTEM:CONSOLE
        )
    
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    Empaerior
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    Empaerior
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL2;"
        "SDL2main;"
        "SDL2_mixer;"
		"vulkan-1;"
        "freetype;")
		#"libtmxlite")



target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2/lib/x86;"
    
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_mixer/lib/x86;"
       
	   "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/freetype/lib/x86"
	   
	
		
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanSDK/Lib"
		
		
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2/lib/x64;"
 
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_mixer/lib/x64;"
  

		
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/freetype/lib/x64"
		
		"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanSDK/Lib"
    )
endif()

