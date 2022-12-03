#pragma once
#include "SFML/Graphics.hpp"

class Entity;
class PhysicsComponent {
    public:
        void update(float dt, Entity& target);
    private:
    // TODO: consider possibility of moving this to movement component
        float friction_ {0.01f};
        float acceleration_ {0.1f};
        float speed_ {200};
        sf::Vector2f velocity_ {0, 0};
};