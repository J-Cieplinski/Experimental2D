#include "State.hpp"

State::State(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game) : targetWindow_(targetWindow), game_(game) {

}

State::~State() {
    targetWindow_.reset();
}

void State::checkForGameQuit() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        quit_ = true;
    }
}

bool State::isQuitting() const {
    return quit_;
}

bool State::isPaused() const {
    return paused_;
}

void State::unpause() {
    paused_ = false;
}

void State::pause() {
    paused_ = true;
}
