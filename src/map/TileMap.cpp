#include <algorithm>
#include <fstream>
#include "Tile.hpp"
#include "TileMap.hpp"
#include "NormalTile.hpp"

TileMap::TileMap(TextureManager& textureManager) : textureManager_(textureManager) {
    //Sort so that all the tiles are in their render order
    updateDeffered();
}

sf::Texture& TileMap::getTilesTexture() {
    return *tilesTexture_;
}

void TileMap::render(sf::RenderTarget& target) {
    for(const auto& tilesY : tiles_) {
        for(const auto& tile : tilesY) {
            if (!tile || tile->getLayer() == MapLayer::FOREGROUND) {
                continue;
            }
            tile->render(target);
        }
    }
}

void TileMap::defferedRender(sf::RenderTarget& target) {
    for(const auto& tile : renderDefferedTiles_) {
        tile->render(target);
    }
}

void TileMap::loadMap() {
    std::ifstream map("map.bin", std::ios::binary);

    std::vector<TileSaveData> mapTiles;
    unsigned int len {0};
    map.read(reinterpret_cast<char*>(&len), sizeof(unsigned int));
    auto temp = new char[len + 1];
    map.read(temp, len);
    temp[len] = '\0';
    loadTexture(temp);
    delete[] temp;

    unsigned int maxX {0};
    unsigned int maxY {0};

    while(true) {
        TileSaveData data;
        map.read(reinterpret_cast<char*>(&data), sizeof(TileSaveData));
        if(map.eof()) break;
        mapTiles.push_back(data);
        maxX = data.position.x > maxX ? data.position.x : maxX;
        maxY = data.position.y > maxY ? data.position.y : maxY;
    }

    tiles_.resize(maxX / gridSize_);
    for(auto& tilesY : tiles_) {
        tilesY.resize(maxY/gridSize_);
    }

    for(const auto& savedTile : mapTiles) {
        TileData tile(*tilesTexture_);
        tile.layer = savedTile.layer;
        tile.textureRect = savedTile.textureRect;
        tile.position = savedTile.position;
        addTile(tile);
    }
}

void TileMap::saveMap() {
    std::ofstream map("map.bin", std::ios::binary);
    unsigned int len = texturePath_.length();
    map.write(reinterpret_cast<char*>(&len), sizeof(unsigned int));
    map.write(texturePath_.c_str(), len);

    for(const auto& tilesY : tiles_) {
        for(const auto& tile : tilesY) {
            TileSaveData data;
            data.layer = tile->getLayer();
            data.position = tile->getPosition();
            data.textureRect = tile->getIntRect();
            map.write(reinterpret_cast<char *>(&data), sizeof(TileSaveData));
        }
    }
    map.close();
}

void TileMap::addTile(const TileData& tile) {
    auto ptr = std::shared_ptr<Tile>(new NormalTile(tile));
    tiles_[tile.position.x / gridSize_ - 1][tile.position.y / gridSize_ - 1] = ptr;
    if(ptr->getLayer() == MapLayer::FOREGROUND) {
        renderDefferedTiles_.insert(ptr);
    }
}

void TileMap::removeTile(Tile* tile) {
    auto tileExistInCollection = [&](auto& el) {
        return el.get() == tile;
    };

    for(auto& tilesY : tiles_) {
        const unsigned int erased = std::erase_if(tilesY, tileExistInCollection);
        if(erased) break;
    }
    std::erase_if(renderDefferedTiles_, tileExistInCollection);
}

void TileMap::updateDeffered() {
    for(const auto& tilesY : tiles_) {
        for(const auto& tile : tilesY) {
            if(!tile) continue;
            if (tile->getLayer() == MapLayer::FOREGROUND) {
                renderDefferedTiles_.insert(tile);
            }
        }
    }
}

void TileMap::loadTexture(const char *filePath) {
    texturePath_ = filePath;
    textureManager_.loadAsset(filePath, Textures::MAP);
    tilesTexture_ = &textureManager_.getAsset(Textures::MAP);
}
