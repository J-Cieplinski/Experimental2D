#pragma once
#include "SFML/Graphics.hpp"

class EntityControlComponent;
class PhysicsComponent;
class GraphicsComponent;

class Entity {
    public:
        Entity(EntityControlComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
        sf::Vector2f position_ {0, 0};
        sf::Vector2f direction_ {0, 0};

        void update(float dt);
        void render(sf::RenderTarget& target);
    private:
        std::unique_ptr<EntityControlComponent> input_;
        std::unique_ptr<PhysicsComponent> physics_;
        std::unique_ptr<GraphicsComponent> graphics_;
};