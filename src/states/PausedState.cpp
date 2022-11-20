#include "PausedState.hpp"
#include "GameState.hpp"
#include "../Game.hpp"

PausedState::PausedState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game, "configs/testKeybinds.json") {
}

void PausedState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(!targetWindow_) {
        return;
    }
    if(sf::Keyboard::isKeyPressed(keybinds_["BACK"])) {
        game_->changeState(States::GAME);
    }
}

void PausedState::update(const float dt) {
    if(paused_ || quit_) {
        return;
    }
}

void PausedState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Blue);
}

void PausedState::cleanup() {
    game_ = nullptr;
}
