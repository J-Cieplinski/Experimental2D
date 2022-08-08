#include <algorithm>
#include <fstream>
#include <cassert>
#include "Tile.hpp"
#include "TileMap.hpp"
#include "NormalTile.hpp"

TileMap::TileMap(){
    constexpr unsigned int maxX = 100;
    constexpr unsigned int maxY = 100;
    gridSize_ = 64;

    tiles_.reserve(maxX*maxY);

    //Sort so that all the tiles are in their render order
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

struct TileSaveData {
    char texturePath[100];
    sf::Vector2f position;
    sf::IntRect textureRect;
    MapLayer layer;
};

void TileMap::loadMap() {
    std::ifstream map("map.bin", std::ios::binary);

    std::vector<TileSaveData> mapTiles;
    while(true) {
        TileSaveData data;
        map.read(reinterpret_cast<char*>(&data), sizeof(TileSaveData));
        if(map.eof()) break;
        mapTiles.push_back(data);
    }

    texturePath_ = mapTiles[0].texturePath;
    assert(tilesTexture_.loadFromFile(texturePath_));
    for(const auto& savedTile : mapTiles) {
        TileData tile(tilesTexture_);
        tile.layer = savedTile.layer;
        tile.textureRect = savedTile.textureRect;
        tile.position = savedTile.position;
        addTile(new NormalTile(tile));
    }
}

void TileMap::saveMap() {
    std::ofstream map("map.bin", std::ios::binary);
    TileSaveData data;
    strcpy_s(data.texturePath, texturePath_.c_str());

    for(const auto& tile : tiles_) {
        data.layer = tile->getLayer();
        data.position = tile->getPosition();
        data.textureRect = tile->getIntRect();
        map.write(reinterpret_cast<char*>(&data), sizeof(TileSaveData));
    }
    map.close();
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

void TileMap::loadTexture(const char *filePath) {
    texturePath_ = filePath;
    assert(tilesTexture_.loadFromFile(texturePath_));
}
