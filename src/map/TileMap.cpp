#include <algorithm>
#include "Tile.hpp"
#include "TileMap.hpp"

TileMap::TileMap(){
    unsigned int maxX = 50000;
    unsigned int maxY = 50000;

    tiles_.reserve(maxX);
    for(auto& tile : tiles_) {
        tile.reserve(maxY);
    }

    //Sort so that all of the tiles are in their render order
    for(auto& tilesY : tiles_) {
        std::sort(tilesY.begin(), tilesY.end());
    }

    for(const auto& tilesY : tiles_) {
        for(const auto tile : tilesY) {
            if(tile->getLayer() == MapLayer::FOREGROUND) {
                renderDefferedTiles_.push_back(tile);
            }
        }
    }
}

void TileMap::render(sf::RenderWindow* target) {
    for(const auto& tilesY : tiles_) {
        for(const auto tile : tilesY) {
            if(tile->getLayer() == MapLayer::FOREGROUND) {
                break;  //because we sort so that all foreground tiles are last ones in vector
            }
            tile->render(target);
        }
    }
}

void TileMap::defferedRender(sf::RenderWindow* target) {
    for(const auto& tile : renderDefferedTiles_) {
        tile->render(target);
    }
}

void TileMap::loadMap() {

}

void TileMap::saveMap() {

}
