#pragma once
#include "State.hpp"
#include "../gui/Button.hpp"

class MainMenuState : public State {
        public:
        MainMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(float dt) override;
        void update(float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;

        private:
        using ComponentPtr = std::unique_ptr<gui::Component>;
        std::vector<ComponentPtr> buttons_;
        sf::RectangleShape background_;

        void initButtons();
};