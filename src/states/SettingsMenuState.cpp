#include "SettingsMenuState.hpp"

SettingsMenuState::SettingsMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game, const sf::Texture& backgroundImage, const sf::Font& font)
    : State(targetWindow, game), font_(font), backgroundImage_(backgroundImage) {
        background_.setSize(sf::Vector2f(targetWindow->getSize()));
        background_.setTexture(&backgroundImage);

}

void SettingsMenuState::updateFromInput(const float dt) {

}

void SettingsMenuState::update(const float dt) {

}

void SettingsMenuState::render(sf::RenderTarget* target) {

}

void SettingsMenuState::cleanup() {

}
