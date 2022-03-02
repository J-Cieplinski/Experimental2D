#pragma once
#include "SFML/Graphics.hpp"

class Entity;
class GraphicsComponent {
    public:
        GraphicsComponent();

        void render(sf::RenderTarget& target);
        void update(const Entity& entity);
    private:
        sf::RectangleShape shape_;
};