#include "State.hpp"

State::State(std::shared_ptr<sf::RenderWindow> targetWindow) : m_targetWindow(targetWindow) {

}

State::~State() {
    m_targetWindow.reset();
}

void State::checkForExit() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        m_quit = true;
    }
}

bool State::isQuitting() const {
    return m_quit;
}
