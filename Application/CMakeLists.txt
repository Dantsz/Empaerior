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


find_package(SDL2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)
find_package(unofficial-vulkan-memory-allocator CONFIG REQUIRED)
find_package(Vulkan)
find_path(STB_INCLUDE_DIRS "stb.h")
find_package(glm CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

################################################################################
# Include directories
################################################################################

    target_include_directories(${PROJECT_NAME} PUBLIC
		${STB_INCLUDE_DIRS}
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
    spdlog::spdlog_header_only
    freetype
    Vulkan::Vulkan
    unofficial::vulkan-memory-allocator::vulkan-memory-allocator
    glm::glm
    SDL2::SDL2_mixer
    SDL2::SDL2main
    SDL2::SDL2
)



