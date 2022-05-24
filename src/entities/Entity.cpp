#include "Entity.hpp"

Entity::Entity(EntityControlComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
    : input_(input),
      physics_(physics),
      graphics_(graphics)
{

}

void Entity::update(float dt) {
    input_->update(*this);
    physics_->update(dt, *this);
    switch(input_->getState()){
        case MovementState::IDLE:
            graphics_->getAnimationComponent().play("IDLE", dt);
            break;
        case MovementState::MOVING_RIGHT:
            graphics_->getAnimationComponent().play("RIGHT", dt);
            break;
        case MovementState::MOVING_LEFT:
            graphics_->getAnimationComponent().play("LEFT", dt);
            break;
    }
    graphics_->update(*this);
}

void Entity::render(sf::RenderTarget& target) {
    graphics_->render(target);
}
