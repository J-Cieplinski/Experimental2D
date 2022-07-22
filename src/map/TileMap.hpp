#pragma once
#include <vector>

class Tile;

class TileMap {
    private:
        std::vector<std::vector<Tile*>> tiles_;
    public:
        TileMap();
};