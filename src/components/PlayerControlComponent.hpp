#pragma once

#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include "EntityControlComponent.hpp"

class PlayerControlComponent : public EntityControlComponent {
    public:
        PlayerControlComponent(const std::map<std::string, sf::Keyboard::Key>& keybinds);
        void update(Entity& target) override;
    private:
        std::map<std::string, sf::Keyboard::Key> keybinds_;
};