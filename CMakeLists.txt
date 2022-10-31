cmake_minimum_required(VERSION 3.16)
project(Experimental2D CXX)

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB Json dependencies/nlohmann/*)

add_executable(Experimental2D src/main.cpp src/Game.cpp src/AssetsManager.hpp)
target_link_libraries(Experimental2D States Map Components Entities Gui)