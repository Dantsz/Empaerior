cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)
set(CMAKE_SUPPRESS_REGENERATION true)


set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(Empaerior CXX)

add_subdirectory(Application)
add_subdirectory(Empaerior)

