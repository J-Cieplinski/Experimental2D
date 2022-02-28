#include "Entity.hpp"
#include "../components/InputComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/PhysicsComponent.hpp"

Entity::Entity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
    : input_(input),
      physics_(physics),
      graphics_(graphics)
{

}

void Entity::update(const float dt) {
    input_->update(*this);
    physics_->update(dt, *this);
    graphics_->update(*this);
}

void Entity::render(sf::RenderTarget& target) {
    graphics_->render(target);
}
