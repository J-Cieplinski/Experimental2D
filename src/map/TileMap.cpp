#include <algorithm>
#include <fstream>
#include "Tile.hpp"
#include "TileMap.hpp"
#include "NormalTile.hpp"

TileMap::TileMap(TextureManager& textureManager) : textureManager_(textureManager) {
}

sf::Texture& TileMap::getTilesTexture() const {
    return *tilesTexture_;
}

void TileMap::render(sf::RenderTarget& target) const {
    for(const auto& tilesY : tiles_) {
        for (const auto &tilesZ: tilesY) {
            for (int i = 0; static_cast<MapLayer>(i) <= MapLayer::ENTITY; ++i) {
                if(!tilesZ[i]) continue;
                tilesZ[i]->render(target);
            }
        }
    }
}

void TileMap::deferredRender(sf::RenderTarget& target) const {
    for(const auto& tilesY : tiles_) {
        for (const auto &tilesZ: tilesY) {
            for (int i = static_cast<int>(MapLayer::ENTITY) + 1; i < tiles_[0][0].size(); ++i) {
                if(!tilesZ[i]) continue;
                tilesZ[i]->render(target);
            }
        }
    }
}

void TileMap::loadMap(int maxX, int maxY) {
    std::ifstream map("map.bin", std::ios::binary);
    constexpr int maxZ = static_cast<int>(MapLayer::MAX_LAYERS);

    std::vector<TileSaveData> mapTiles;
    unsigned int len {0};
    map.read(reinterpret_cast<char*>(&len), sizeof(unsigned int));

    auto temp = new char[len + 1];
    map.read(temp, len);
    temp[len] = '\0';
    loadTexture(temp);
    delete[] temp;

    while(true) {
        TileSaveData data;
        map.read(reinterpret_cast<char*>(&data), sizeof(TileSaveData));
        if(map.eof()) break;
        mapTiles.push_back(data);
        maxX = data.position.x > maxX ? data.position.x : maxX;
        maxY = data.position.y > maxY ? data.position.y : maxY;
    }

    createMap(maxX, maxY, maxZ);

    for(const auto& [position, textureRect, layer] : mapTiles) {
        TileData tile(*tilesTexture_);
        tile.layer = layer;
        tile.textureRect = textureRect;
        tile.position = position;
        addTile(tile);
    }
}

void TileMap::saveMap() {
    std::ofstream map("map.bin", std::ios::binary);
    unsigned int len = texturePath_.length();
    map.write(reinterpret_cast<char*>(&len), sizeof(unsigned int));
    map.write(texturePath_.c_str(), len);

    for(const auto& tilesZ : tiles_) {
        for (const auto &tilesY: tilesZ) {
            for (const auto &tile: tilesY) {
                if (!tile) continue;
                TileSaveData data;
                data.layer = tile->getLayer();
                data.position = tile->getPosition();
                data.textureRect = tile->getIntRect();
                map.write(reinterpret_cast<char *>(&data), sizeof(TileSaveData));
            }
        }
    }
    map.close();
}

void TileMap::addTile(const TileData& tile) {
    auto ptr = std::shared_ptr<Tile>(new NormalTile(tile));
    const auto indexX = tile.position.x / gridSize_ - 1;
    const auto indexY = tile.position.y / gridSize_ - 1;
    const auto indexZ = static_cast<int>(tile.layer);
    tiles_[indexX >= 0 ? indexX : 0][indexY >= 0 ? indexY : 0][indexZ] = ptr;
}

void TileMap::removeTile(Tile* tile) {
    for(auto& tilesY : tiles_) {
        for (auto& tilesZ: tilesY) {
            for(auto& tileZ : tilesZ)
            {
                if(tileZ.get() == tile) {
                    tileZ.reset();
                    return;
                }
            }
        }
    }
}

void TileMap::loadTexture(const char *filePath) {
    texturePath_ = filePath;
    textureManager_.loadAsset(filePath, Textures::MAP);
    tilesTexture_ = &textureManager_.getAsset(Textures::MAP);
}

void TileMap::createMap(int x, int y, int z) {
    tiles_.resize(x / gridSize_);
    for(auto& tilesY : tiles_) {
        tilesY.resize(y / gridSize_);
        for(auto& tilesZ: tilesY) {
            tilesZ.resize(z);
        }
    }
}

Tile *TileMap::getTileAtPos(int x, int y, int z) const {
    const int indexX = x / gridSize_ - 1;
    const int indexY = y / gridSize_ - 1;
    return tiles_[indexX >= 0 ? indexX : 0][indexY >= 0 ? indexY : 0][z].get();
}
