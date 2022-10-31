cmake_minimum_required(VERSION 3.16)

IF (WIN32)
    set(SFML_DIR "C:\\SFML-2.5.1\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(sources
        AnimationComponent.cpp
        EntityControlComponent.cpp
        GraphicsComponent.cpp
        PhysicsComponent.cpp
        PlayerControlComponent.cpp

        AnimationComponent.hpp
        EntityControlComponent.hpp
        GraphicsComponent.hpp
        PhysicsComponent.hpp
        PlayerControlComponent.hpp
        )

add_library(Components STATIC ${sources})
target_link_libraries(Components sfml-graphics)
