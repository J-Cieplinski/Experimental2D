#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class Tile;

class TileMap {
    private:
        std::vector<std::vector<Tile*>> tiles_;
        std::vector<Tile*> renderDefferedTiles_;
        sf::Texture tilesTexture_;
    public:
        TileMap();
        void render(sf::RenderWindow* target);
        void defferedRender(sf::RenderWindow* target);
        void loadMap();
        void saveMap();
};