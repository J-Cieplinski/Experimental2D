#include "GraphicsComponent.hpp"
#include "../entities/Entity.hpp"

GraphicsComponent::GraphicsComponent() {
    shape_.setSize({10, 10});
    shape_.setFillColor(sf::Color::Black);
}
void GraphicsComponent::render(sf::RenderTarget& target) {
    target.draw(shape_);
}

void GraphicsComponent::update(const Entity& entity) {
    shape_.setPosition(entity.position_);
}
