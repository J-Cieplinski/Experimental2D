#include "Game.hpp"
#include "../dependencies/nlohmann/json.hpp"
#include "states/MainMenuState.hpp"
#include "states/GameState.hpp"
#include "states/PausedState.hpp"
#include "states/SettingsMenuState.hpp"
#include "states/EditorState.hpp"
#include <fstream>

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
    initResources();
    initStates();
}

Game::~Game() {
    states_.clear();
}

void Game::switchState(States stateId) {
    // create the new state if not existing
    if(!states_[stateId]) {
        states_[stateId] = createState(stateId);
    }

    // unpause the new state
    currentState_ = states_[stateId].get();
    currentState_->unpause();
}

void Game::changeState(States stateId) {
    // cleanup the current state
	if (!states_.empty()) {
        currentState_->cleanup();
        auto it = std::find_if(states_.begin(), states_.end(), [&](const auto& el) {
            return el.second.get() == currentState_;
        });
        states_.erase(it);
        currentState_ = nullptr;
	}

    switchState(stateId);
}

void Game::pushState(States stateId) {
    // pause current state
	if (currentState_) {
		currentState_->pause();
	}

    switchState(stateId);
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
        currentState_->updateFromInput(dt_);
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

template<>
TextureManager &Game::getAssetsManager() {
    return textureManager_;
}

template<>
FontsManager &Game::getAssetsManager() {
    return fontsManager_;
}

std::unique_ptr<State> Game::createState(States state) {
    switch (state) {
        case States::GAME:
            return std::make_unique<GameState>(window_, this);
        case States::PAUSED:
            return std::make_unique<PausedState>(window_, this);
        case States::MENU:
            return std::make_unique<MainMenuState>(window_, this);
        case States::SETTINGS:
            return std::make_unique<SettingsMenuState>(window_, this);
        case States::EDITOR:
            return std::make_unique<EditorState>(window_, this);
        default:
            return nullptr;
    }
}

void Game::initResources() {
    textureManager_.loadAsset("assets/textures/characters/PC/Template_Male.png", Textures::PLAYER);
    fontsManager_.loadAsset("assets/fonts/LeagueGothic.ttf", Fonts::MAIN);
    textureManager_.loadAsset("assets/textures/mainMenu/background.png", Textures::BACKGROUND);
}
