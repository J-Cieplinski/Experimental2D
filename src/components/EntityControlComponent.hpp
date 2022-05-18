#pragma once

enum class MovementState {
    MOVING_RIGHT,
    MOVING_LEFT,
    MOVING_UP,
    MOVING_DOWN,
    IDLE
};

class Entity;
class EntityControlComponent {
    public:
        virtual void update(Entity& target);
        MovementState getState();
    protected:
        MovementState state_;
};