#pragma once
#include <vector>
#include <set>
#include "SFML/Graphics.hpp"
#include "../Game.hpp"

class Tile;


class TileMap {
    private:
        std::vector<std::shared_ptr<Tile>> tiles_;
        std::set<std::shared_ptr<Tile>> renderDefferedTiles_;
        sf::Texture* tilesTexture_;
        TextureManager& textureManager_;
        std::string texturePath_;
        unsigned int gridSize_;
        bool isSorted_ {false};
    public:
        TileMap(TextureManager& textureManager);

        sf::Texture& getTilesTexture();
        void loadTexture(const char* filePath);
        void render(sf::RenderTarget& target);
        void defferedRender(sf::RenderTarget& target);
        void loadMap();
        void saveMap();
        void addTile(Tile* tile);
        void removeTile(Tile* tile);
        void sortTiles();
        void updateDeffered();
};