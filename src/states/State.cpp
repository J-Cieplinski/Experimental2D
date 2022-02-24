#include "State.hpp"

State::State(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game) : m_targetWindow(targetWindow), m_game(game) {

}

State::~State() {
    m_targetWindow.reset();
}

void State::checkForExit() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        m_quit = true;
    }
}

bool State::isQuitting() const {
    return m_quit;
}

bool State::isPaused() const {
    return m_paused;
}

void State::unpause() {
    m_paused = false;
}

void State::pause() {
    m_paused = true;
}
