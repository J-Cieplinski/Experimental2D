#include "PausedState.hpp"
#include "GameState.hpp"
#include "../Game.hpp"

PausedState::PausedState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {

}

void PausedState::updateFromInput(const float dt) {
    checkForExit();
    if(!m_targetWindow) {
        return;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        m_game->changeState(States::GAME);
    }
}

void PausedState::update(const float dt) {
    if(m_paused || m_quit) {
        return;
    }
    updateFromInput(dt);
}

void PausedState::render(sf::RenderTarget* target) {
    target = target ? target : m_targetWindow.get();
    target->clear(sf::Color::Blue);
}

void PausedState::cleanup() {
    m_game = nullptr;
}
