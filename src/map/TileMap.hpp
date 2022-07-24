#pragma once
#include <vector>
#include <set>
#include "SFML/Graphics.hpp"

class Tile;

class TileMap {
    private:
        std::vector<Tile*> tiles_;
        std::set<Tile*> renderDefferedTiles_;
        sf::Texture tilesTexture_;
        bool isSorted_ {false};
    public:
        TileMap();
        void render(sf::RenderTarget& target);
        void defferedRender(sf::RenderTarget& target);
        void loadMap();
        void saveMap();
        void addTile(Tile* tile);
        void removeTile(Tile* tile);
        void sortTiles();
        void updateDeffered();
};