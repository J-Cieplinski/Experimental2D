#include "GameState.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> targetWindow)
    : State(targetWindow) {

}

void GameState::updateFromInput(const float dt) {
    checkForExit();
}

void GameState::update(const float dt) {
    updateFromInput(dt);
}

void GameState::render(sf::RenderTarget* target) {
    target = target ? target : m_targetWindow.get();
}

void GameState::exitState() {

}
