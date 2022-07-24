#pragma once
#include "SFML/Graphics.hpp"
#include "../util.hpp"

class Tile {
    private:
        sf::Sprite tile_;
        bool isCollidable_;
        MapLayer layer_;

    public:
        const sf::Vector2f& getPosition() const;
        const MapLayer getLayer() const;
        friend bool operator<(const Tile& left, const Tile& right) {
            return left.layer_ < right.layer_;
        };

        virtual void render(sf::RenderTarget& target) = 0;
};