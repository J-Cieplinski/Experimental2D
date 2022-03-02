#pragma once

class Entity;
class EntityControlComponent {
    public:
        virtual void update(Entity& target);
};