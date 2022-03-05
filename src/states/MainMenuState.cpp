#include <memory>
#include <cassert>
#include <fstream>
#include "../../dependencies/nlohmann/json.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "../Game.hpp"
#include "../util.hpp"

using json = nlohmann::json;

void MainMenuState::initButtons() {
    std::map<std::string, std::function<void()>> mainMenuFunc;
    mainMenuFunc["Start"] = [&]() { game_->pushState(States::GAME, std::make_unique<GameState>(targetWindow_, game_)); };
    mainMenuFunc["Settings"] = [&]() {  };
    mainMenuFunc["Exit"] = [&]() { quit_ = true; };
    mainMenuFunc["Editor"] = [&]() {  };


    auto halfWindow = sf::Vector2f(targetWindow_->getSize() / 2u);

    std::ifstream buttonsConfigFile("configs/buttons.json");
    assert(buttonsConfigFile.is_open());

    auto buttonsConfig = json::parse(buttonsConfigFile);
    auto mainMenu = buttonsConfig["mainMenu"];

    for(auto& button : mainMenu["buttons"]) {
        auto size = sf::Vector2f(button["width"], button["height"]);
        auto offset = button["centerOffset"];
        std::string name = button["name"];

        uint8_t charSize {0};

        try {
            charSize = button.at("charSize");
        } catch(const json::out_of_range& e) {
            charSize = mainMenu["charSize"];
        }

        buttons_.push_back({size, halfWindow + sf::Vector2f(offset["x"], offset["y"]), name, font_.get(), charSize, mainMenuFunc.at(name)});
    }

    for(auto& button : buttons_) {
        addObserver(&button);
    }
}

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {
        font_ = std::make_unique<sf::Font>();
        assert(font_->loadFromFile("assets/fonts/LeagueGothic.ttf"));

        initButtons();
}

void MainMenuState::updateFromInput(const float dt) {
    checkForGameQuit();

    if(game_->event_.type == sf::Event::MouseMoved) {
        updateMousePos();

        for(auto& button : buttons_) {
            button.update(mouseWindowPos_);
        }
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for(const auto& observer : observers_) {
            observer->onNotify(Event::MOUSE_CLICK, mouseWindowPos_);
        }
    }
}

void MainMenuState::update(const float dt) {
    if(paused_ || quit_) {
        return;
    }

    updateFromInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Black);
    for(auto& button : buttons_) {
        button.render(*target);
    }
}

void MainMenuState::cleanup() {
    game_ = nullptr;
}
