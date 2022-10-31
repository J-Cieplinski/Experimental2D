cmake_minimum_required(VERSION 3.16)

IF (WIN32)
    set(SFML_DIR "C:\\SFML-2.5.1\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(sources
        EditorState.cpp
        GameState.cpp
        MainMenuState.cpp
        PausedState.cpp
        SettingsMenuState.cpp
        State.cpp

        EditorState.hpp
        GameState.hpp
        MainMenuState.hpp
        PausedState.hpp
        SettingsMenuState.hpp
        State.hpp
        )

add_library(States STATIC ${sources})
target_link_libraries(States sfml-graphics)
