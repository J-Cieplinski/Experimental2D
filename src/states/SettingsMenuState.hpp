#pragma once
#include "State.hpp"
#include "../gui/Button.hpp"
#include "../gui/DropdownList.hpp"

class SettingsMenuState : public State {
    public:
        SettingsMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(const float dt) override;
        void update(const float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;
    private:
        std::vector<std::unique_ptr<gui::Component>> buttons_;
        sf::Font font_;
        sf::RectangleShape background_;
};