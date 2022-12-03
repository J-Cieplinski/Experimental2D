#pragma once
#include "../util.hpp"

class Entity;
class EntityControlComponent {
    public:
        virtual void update(Entity& target);
        EntityState getState() const;
    protected:
        EntityState state_ {EntityState::IDLE};
};