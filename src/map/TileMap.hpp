#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../Game.hpp"
#include "Tile.hpp"

class TileMap {
    private:
        struct TileSaveData {
            sf::Vector2f position;
            sf::IntRect textureRect;
            MapLayer layer;
        };

        std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> tiles_;
        sf::Texture* tilesTexture_;
        TextureManager& textureManager_;
        std::string texturePath_;
        unsigned int gridSize_ {64};
    public:
        TileMap(TextureManager& textureManager);

        sf::Texture& getTilesTexture() const;
        void loadTexture(const char* filePath);
        void render(sf::RenderTarget& target) const;
        void deferredRender(sf::RenderTarget& target) const;
        void createMap(int x, int y, int z);
        void loadMap(int maxX = 0, int maxY = 0);
        void saveMap();
        void addTile(const TileData& tile);
        void removeTile(Tile* tile);
        Tile* getTileAtPos(int x, int y, int z) const;
};