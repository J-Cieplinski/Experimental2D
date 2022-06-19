#pragma once
#include "../util.hpp"

class Entity;
class EntityControlComponent {
    public:
        virtual void update(Entity& target);
        EntityState getState();
    protected:
        EntityState state_;
};