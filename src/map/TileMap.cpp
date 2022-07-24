#include <algorithm>
#include "Tile.hpp"
#include "TileMap.hpp"

TileMap::TileMap(){
    constexpr unsigned int maxX = 5000;
    constexpr unsigned int maxY = 5000;

    tiles_.reserve(maxX*maxY);

    //Sort so that all of the tiles are in their render order
    sortTiles();
    updateDeffered();
}

void TileMap::render(sf::RenderTarget& target) {
    for(const auto& tile : tiles_) {
        if(tile->getLayer() == MapLayer::FOREGROUND) {
            break;  //because we sort so that all foreground tiles are last ones in vector
        }
        tile->render(target);
    }
}

void TileMap::defferedRender(sf::RenderTarget& target) {
    for(const auto& tile : renderDefferedTiles_) {
        tile->render(target);
    }
}

void TileMap::loadMap() {

}

void TileMap::saveMap() {

}

void TileMap::addTile(Tile* tile) {
    tiles_.push_back(tile);
    if(tile->getLayer() == MapLayer::FOREGROUND) {
        renderDefferedTiles_.insert(tile);
    }
    sortTiles();
}

void TileMap::removeTile(Tile* tile) {
    std::erase(tiles_, tile);
    renderDefferedTiles_.erase(tile);
}

void TileMap::updateDeffered() {
    for(const auto& tile : tiles_) {
        if(tile->getLayer() == MapLayer::FOREGROUND) {
            renderDefferedTiles_.insert(tile);
        }
    }
}

void TileMap::sortTiles() {
    std::sort(tiles_.begin(), tiles_.end());
    isSorted_ = true;
}
