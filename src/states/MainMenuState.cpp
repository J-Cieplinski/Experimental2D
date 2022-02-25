#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "../Game.hpp"
#include "../util.hpp"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {
}

void MainMenuState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["CONFIRM"])) {
        game_->pushState(States::GAME, std::make_unique<GameState>(targetWindow_, game_));
    }
}

void MainMenuState::update(const float dt) {
    if(paused_ || quit_) {
        return;
    }
    updateFromInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Cyan);
}

void MainMenuState::cleanup() {
    game_ = nullptr;
}
