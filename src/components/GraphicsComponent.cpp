#include "GraphicsComponent.hpp"
#include "../entities/Entity.hpp"

GraphicsComponent::GraphicsComponent() : animationComponent_(sprite_) {
    //sprite_.setScale(2,2);
    //sprite_.setColor(sf::Color::Black);
}
void GraphicsComponent::render(sf::RenderTarget& target) const {
    target.draw(sprite_);
}

void GraphicsComponent::update(const Entity& entity) {
    sprite_.setPosition(entity.position_);
}

AnimationComponent& GraphicsComponent::getAnimationComponent() {
    return animationComponent_;
}
