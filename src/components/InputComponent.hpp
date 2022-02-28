#pragma once
#include "../entities/Entity.hpp"

class InputComponent {
    public:
        InputComponent(const std::map<std::string, sf::Keyboard::Key>& keybinds);
        void update(Entity& target);
    private:
        std::map<std::string, sf::Keyboard::Key> keybinds_;
};