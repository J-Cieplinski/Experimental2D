#pragma once
#include <vector>
#include <set>
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

        std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
        std::set<std::shared_ptr<Tile>> renderDefferedTiles_;
        sf::Texture* tilesTexture_;
        TextureManager& textureManager_;
        std::string texturePath_;
        unsigned int gridSize_ {64};
    public:
        TileMap(TextureManager& textureManager);

        sf::Texture& getTilesTexture();
        void loadTexture(const char* filePath);
        void render(sf::RenderTarget& target);
        void defferedRender(sf::RenderTarget& target);
        void loadMap();
        void saveMap();
        void addTile(const TileData& tile);
        void removeTile(Tile* tile);
        void updateDeffered();
};