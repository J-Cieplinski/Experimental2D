#include "State.hpp"
#include "../../dependencies/nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

void State::initKeybinds(const char* configFile) {
    std::ifstream keybindsConfig(configFile);
    assert(keybindsConfig.is_open());

    auto keybinds = json::parse(keybindsConfig);
    keybindsConfig.close();

    for(auto& keybind : keybinds.items()) {
        keybinds_[keybind.key()] = static_cast<sf::Keyboard::Key>(keybind.value());
    }
}

State::State(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game, const char* keybindsConfig) : targetWindow_(targetWindow), game_(game) {
    initKeybinds(keybindsConfig);
}

void State::checkForGameQuit() {
    if(sf::Keyboard::isKeyPressed(keybinds_["QUIT"])) {
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

void State::updateMousePos() {
    mouseScreenPos_ = sf::Mouse::getPosition();
    mouseWindowPos_ = sf::Mouse::getPosition(*targetWindow_);
    mouseViewPos_ = targetWindow_->mapPixelToCoords(mouseWindowPos_);
}

void State::addObserver(Observer* observer) {
    observers_.emplace(observer);
}

void State::removeObserver(Observer* observer) {
    observers_.erase(observer);
}

const sf::Vector2i& State::getMouseWindowPos() const {
    return mouseWindowPos_;
}

void State::update(const float dt) {
    if(paused_ || quit_ || quitState_) {
        return;
    }

    updateFromInput(dt);
}

