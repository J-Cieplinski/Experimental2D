#pragma once

#include "Tile.hpp"

class NormalTile : public Tile {
    public:
        NormalTile(const TileData& tiledata);
        void render(sf::RenderTarget& target) override;
};