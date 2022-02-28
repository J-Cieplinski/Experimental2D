#pragma once
#include "SFML/Graphics.hpp"
#include "../entities/Entity.hpp"

class GraphicsComponent {
    public:
        GraphicsComponent();

        void render(sf::RenderTarget& target);
        void update(const Entity& entity);
    private:
        sf::RectangleShape shape_;
};