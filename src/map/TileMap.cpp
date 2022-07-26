#include <algorithm>
#include "Tile.hpp"
#include "TileMap.hpp"

TileMap::TileMap(){
    constexpr unsigned int maxX = 100;
    constexpr unsigned int maxY = 100;
    gridSize_ = 64;

    tiles_.reserve(maxX*maxY);

    //Sort so that all of the tiles are in their render order
    sortTiles();
    updateDeffered();
}

sf::Texture& TileMap::getTilesTexture() {
    return tilesTexture_;
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
    auto ptr = std::shared_ptr<Tile>(tile);
    tiles_.push_back(ptr);
    if(ptr->getLayer() == MapLayer::FOREGROUND) {
        renderDefferedTiles_.insert(ptr);
    }
    sortTiles();
}

void TileMap::removeTile(Tile* tile) {
    auto tileExistInCollection = [&](auto& el) {
        return el.get() == tile;
    };

    std::erase_if(tiles_, tileExistInCollection);
    std::erase_if(renderDefferedTiles_, tileExistInCollection);
}

void TileMap::updateDeffered() {
    for(const auto& tile : tiles_) {
        if(tile->getLayer() == MapLayer::FOREGROUND) {
            renderDefferedTiles_.insert(tile);
        }
    }
}

void TileMap::sortTiles() {
    std::sort(tiles_.begin(), tiles_.end(), [&](const auto& lhs, const auto& rhs) {
        return *lhs < *rhs;
    });
    isSorted_ = true;
}
