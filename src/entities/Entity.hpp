#pragma once
#include "SFML/Graphics.hpp"

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

class Entity {
    public:
        Entity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
        sf::Vector2f position_ {0, 0};
        sf::Vector2f direction_ {0, 0};

        void update(const float dt);
        void render(sf::RenderTarget& target);
    private:
        std::unique_ptr<InputComponent> input_;
        std::unique_ptr<PhysicsComponent> physics_;
        std::unique_ptr<GraphicsComponent> graphics_;
};