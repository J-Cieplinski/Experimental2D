#include "GameState.hpp"
#include "../Game.hpp"
#include "PausedState.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {

}

void GameState::updateFromInput(const float dt) {
    checkForExit();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        m_game->pushState(States::PAUSED, std::make_unique<PausedState>(m_targetWindow, m_game));
    }
}

void GameState::update(const float dt) {
    if(m_paused || m_quit) {
        return;
    }
    updateFromInput(dt);
}

void GameState::render(sf::RenderTarget* target) {
    target = target ? target : m_targetWindow.get();
    target->clear(sf::Color::Red);
}

void GameState::cleanup() {
    m_game = nullptr;
}
