#pragma once
#include "SFML/Graphics.hpp"
#include "../util.hpp"

struct TileData {
    TileData(sf::Texture& text) : texture(text) {};
    sf::Texture& texture;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::IntRect textureRect;
    MapLayer layer;
};

class Tile {
    protected:
        sf::Sprite tile_;
        bool isCollidable_ {false};
        MapLayer layer_;

    public:
        Tile(const TileData& tileData);
        virtual ~Tile() {};
        const sf::Vector2f& getPosition() const;
        const sf::IntRect & getIntRect() const;
        const MapLayer getLayer() const;
        friend bool operator<(const Tile& left, const Tile& right) {
            return left.layer_ < right.layer_;
        };

        virtual void render(sf::RenderTarget& target) = 0;
};