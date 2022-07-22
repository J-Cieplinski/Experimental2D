#include <algorithm>
#include "TileMap.hpp"

TileMap::TileMap(){
    unsigned int maxX = 50000;
    unsigned int maxY = 50000;

    tiles_.reserve(maxX);
    for(auto& tile : tiles_) {
        tile.reserve(maxY);
    }

    for(auto& tilesY : tiles_) {
        std::sort(tilesY.begin(), tilesY.end());
    }
}
