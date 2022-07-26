#include "NormalTile.hpp"

NormalTile::NormalTile(const TileData& tiledata) : Tile(tiledata) {
    isCollidable_ = false;
}

void NormalTile::render(sf::RenderTarget& target) {
    target.draw(tile_);
}
