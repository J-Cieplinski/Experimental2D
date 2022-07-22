#include "Tile.hpp"

const sf::Vector2f& Tile::getPosition() const {
    return tile_.getPosition();
}

const MapLayer Tile::getLayer() const {
    return layer_;
}
