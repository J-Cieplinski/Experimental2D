#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "../Game.hpp"
#include "../util.hpp"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {
        addObserver(&testButton_);
}

void MainMenuState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["CONFIRM"])) {
        game_->pushState(States::GAME, std::make_unique<GameState>(targetWindow_, game_));
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for(const auto& observer : observers_) {
            observer->onNotify(Event::MOUSE_CLICK, sf::Vector2f(mouseWindowPos_));
        }
    }
}

void MainMenuState::update(const float dt) {
    if(paused_ || quit_) {
        return;
    }
    updateMousePos();
    updateFromInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Cyan);
    testButton_.render(*target);
}

void MainMenuState::cleanup() {
    game_ = nullptr;
}
