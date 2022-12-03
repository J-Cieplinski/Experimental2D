#pragma once
#include "State.hpp"

class PausedState : public State {
    public:
        PausedState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(float dt) override;
        void update(float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;
};