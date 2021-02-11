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


set(ROOT_NAMESPACE Application)


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

set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug64/Application/"
        OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist64/Application/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release64/Application/"
    )


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
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    Empaerior
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    Empaerior
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2/lib/x64"
    "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_mixer/lib/x64"
	"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/freetype/lib/x64"
	"${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/VulkanSDK/Lib"
    
)


target_link_libraries(${PROJECT_NAME} PUBLIC
    "SDL2"
    "SDL2main"
    "SDL2_mixer"
	"vulkan-1"
    "freetype"
    )
