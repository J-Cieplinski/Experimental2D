#pragma once
#include "SFML/Graphics.hpp"
#include "../components/EntityControlComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/PhysicsComponent.hpp"

class Entity {
    public:
        Entity(EntityControlComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
        Entity() = default;
        sf::Vector2f position_ {0, 0};
        sf::Vector2f direction_ {0, 0};

        void update(float dt);
        void render(sf::RenderTarget& target);
    private:
        std::unique_ptr<EntityControlComponent> input_;
        std::unique_ptr<PhysicsComponent> physics_;
        std::unique_ptr<GraphicsComponent> graphics_;
        MapLayer layer_ {MapLayer::ENTITY};

        void playAnim(float dt);
};