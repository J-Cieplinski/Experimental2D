#include "PlayerControlComponent.hpp"
#include "../entities/Entity.hpp"


PlayerControlComponent::PlayerControlComponent(const std::map<std::string, sf::Keyboard::Key>& keybinds)
    : keybinds_(keybinds)
{

}

void PlayerControlComponent::update(Entity& target) {
    target.direction_ = {0, 0};

    if (sf::Keyboard::isKeyPressed(keybinds_["UP"])) {
        target.direction_.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(keybinds_["DOWN"])) {
        target.direction_.y += 1;
    }

    if(sf::Keyboard::isKeyPressed(keybinds_["LEFT"])) {
        target.direction_.x -= 1;
    }
    if(sf::Keyboard::isKeyPressed(keybinds_["RIGHT"])) {
        target.direction_.x += 1;
    }
}
