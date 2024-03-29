#include "Tile.hpp"

Tile::Tile(const TileData& tileData) :
    layer_(tileData.layer)
{
    tile_.setTexture(tileData.texture);
    tile_.setTextureRect(tileData.textureRect);
    tile_.setPosition(tileData.position);
}

const sf::Vector2f& Tile::getPosition() const {
    return tile_.getPosition();
}

MapLayer Tile::getLayer() const {
    return layer_;
}

const sf::IntRect& Tile::getIntRect() const {
    return tile_.getTextureRect();
}
