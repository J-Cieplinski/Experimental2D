cmake_minimum_required(VERSION 3.19)
project(Experimental2D CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_DIR "C:\\SFML-2.5.1\\lib\\cmake\\SFML")
set(SFML_STATIC_LIBRARIES TRUE)

file(GLOB Json dependencies/nlohmann/*)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(Experimental2D src/main.cpp src/Game.cpp src/states/State.cpp src/states/GameState.cpp src/states/PausedState.cpp)
target_link_libraries(Experimental2D sfml-graphics)