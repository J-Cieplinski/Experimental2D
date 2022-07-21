#include "Game.hpp"
#include "states/MainMenuState.hpp"
#include "../dependencies/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void Game::initStates() {
    states_[States::MENU] = std::make_unique<MainMenuState>(window_, this);
    currentState_ = states_[States::MENU].get();
}

void Game::initWindow() {
    std::ifstream configFile("configs/window.json");
    assert(configFile.is_open());

    auto config = json::parse(configFile);
    configFile.close();
    auto windowConfig = config["window"];

    title_ = windowConfig["title"];
    window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowConfig["width"], windowConfig["height"]), title_);
    if(windowConfig["VSync"]["enabled"]) {
        window_->setVerticalSyncEnabled(true);
        window_->setFramerateLimit(windowConfig["VSync"]["FPScap"]);
    }
}

void Game::run() {
    while(window_->isOpen()) {
        updateDt();
        update();
        render();
    }
}

Game::Game() {
    initWindow();
    initStates();
}

Game::~Game() {
    states_.clear();
}

void Game::changeState(States stateId, std::unique_ptr<State> state) {
    // cleanup the current state
	if (!states_.empty()) {
        currentState_->cleanup();
        auto it = std::find_if(states_.begin(), states_.end(), [&](const auto& el) {
            return el.second.get() == currentState_;
        });
        states_.erase(it);
        currentState_ = nullptr;
	}

    // store the new state if not existing
    if(!states_[stateId]) {
        states_[stateId] = std::move(state);
    }

    // unpause the new state
    currentState_ = states_[stateId].get();
    currentState_->unpause();
}

void Game::pushState(States stateId, std::unique_ptr<State> state) {
    // pause current state
	if (currentState_) {
		currentState_->pause();
	}

	// store the new state if not existing
    if(!states_[stateId]) {
        states_[stateId] = std::move(state);
    }

    // set current state and unpause
    currentState_ = states_[stateId].get();
    currentState_->unpause();
}

void Game::quitState(States stateId) {
    auto stateToQuit = states_[stateId].get();
    if(!stateToQuit || stateToQuit == currentState_) {
        return; //cannot quit current state or non existent one
    }

    auto it = std::find_if(states_.begin(), states_.end(), [&](const auto& el) {
        return el.second.get() == stateToQuit;
    });
    states_.erase(it);
    stateToQuit = nullptr;
}

void Game::pauseAllStates() {
    for(auto& state : states_) {
        state.second->pause();
    }
}

const std::string& Game::getTitle() const {
    return title_;
}

void Game::update() {
    updateEvents();
    if(currentState_) {
        currentState_->update(dt_);
        if(currentState_->isQuitting()) {
            window_->close();
        }
    }
    event_ = sf::Event();
}

void Game::updateEvents() {
    while(window_->pollEvent(event_))
    {
        if(event_.type == sf::Event::Closed) {
            window_->close();
        }
    }
}

void Game::updateDt() {
    dt_ = dtClock_.restart().asSeconds();
}

void Game::render() {
    window_->clear();

    if(currentState_) {
        currentState_->render();
    }

    window_->display();
}
