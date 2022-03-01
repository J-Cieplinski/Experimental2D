#pragma once
#include "../entities/Entity.hpp"

class EntityControlComponent {
    public:
        virtual void update(Entity& target);
};