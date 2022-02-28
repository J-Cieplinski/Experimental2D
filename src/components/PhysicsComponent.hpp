#pragma once
#include "../entities/Entity.hpp"

class PhysicsComponent {
    public:
        void update(float dt, Entity& target);
    private:
        float friction_ {0.01};
        float acceleration_ {0.1};
        float speed_ {200};
        sf::Vector2f velocity_ {0, 0};
};