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
    playAnim(dt);
    graphics_->update(*this);
}

void Entity::render(sf::RenderTarget& target) {
    graphics_->render(target);
}

void Entity::playAnim(float dt) {
    graphics_->getAnimationComponent().play(input_->getState(), dt);
}
