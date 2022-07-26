cmake_minimum_required(VERSION 3.16)
project(Experimental2D CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
IF (WIN32)
    set(SFML_DIR "C:\\SFML-2.5.1\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

file(GLOB Json dependencies/nlohmann/*)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(Experimental2D src/main.cpp src/entities/Entity.cpp src/Game.cpp src/states/State.cpp src/states/GameState.cpp src/states/PausedState.cpp src/states/MainMenuState.cpp
                src/states/SettingsMenuState.cpp src/states/EditorState.cpp src/components/EntityControlComponent.cpp src/components/PhysicsComponent.cpp src/components/GraphicsComponent.cpp
                src/components/PlayerControlComponent.cpp src/gui/Button.cpp src/gui/DropdownList.cpp src/components/AnimationComponent.cpp src/map/Tile.cpp src/map/TileMap.cpp src/map/NormalTile.cpp)
target_link_libraries(Experimental2D sfml-graphics)