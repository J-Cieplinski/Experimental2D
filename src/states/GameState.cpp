#include "GameState.hpp"
#include "../Game.hpp"
#include "PausedState.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {
}

void GameState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["BACK"])) {
        game_->pushState(States::PAUSED, std::make_unique<PausedState>(targetWindow_, game_));
    }
}

void GameState::update(const float dt) {
    if(paused_ || quit_) {
        return;
    }
    updateFromInput(dt);
}

void GameState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Red);
}

void GameState::cleanup() {
    game_ = nullptr;
}


