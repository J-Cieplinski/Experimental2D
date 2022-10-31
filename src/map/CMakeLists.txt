cmake_minimum_required(VERSION 3.16)

IF (WIN32)
    set(SFML_DIR "C:\\SFML-2.5.1\\lib\\cmake\\SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(sources
        NormalTile.cpp
        Tile.cpp
        TileMap.cpp

        NormalTile.hpp
        Tile.hpp
        TileMap.hpp
        )

add_library(Map STATIC ${sources})
target_link_libraries(Map sfml-graphics)
