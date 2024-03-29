#include <memory>
#include <cassert>
#include <fstream>
#include "../../dependencies/nlohmann/json.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "SettingsMenuState.hpp"
#include "EditorState.hpp"
#include "../Game.hpp"
#include "../util.hpp"

using json = nlohmann::json;

void MainMenuState::initButtons() {
    auto& font = game_->getAssetsManager<FontsManager>().getAsset(Fonts::MAIN);
    std::map<std::string, std::function<void()>> mainMenuFunc;
    mainMenuFunc["Start"] = [&]() {
        game_->changeState(States::GAME);
    };
    mainMenuFunc["Settings"] = [&]() {
        game_->pushState(States::SETTINGS);
    };
    mainMenuFunc["Exit"] = [&]() { quit_ = true; };
    mainMenuFunc["Editor"] = [&]() {
        game_->quitState(States::GAME);
        game_->pushState(States::EDITOR);
    };

    auto halfWindow = sf::Vector2f(targetWindow_->getSize() / 2u);

    std::ifstream buttonsConfigFile("configs/buttons.json");
    assert(buttonsConfigFile.is_open());

    auto buttonsConfig = json::parse(buttonsConfigFile);
    auto mainMenu = buttonsConfig["mainMenu"];
    auto buttonsAmount = mainMenu["buttons"].size();
    buttons_.reserve(buttonsAmount);

    for(auto& button : mainMenu["buttons"]) {
        auto size = sf::Vector2f(button["width"], button["height"]);
        auto offset = button["centerOffset"];
        std::string name = button["name"];

        uint8_t charSize {0};

        try {
            charSize = button.at("charSize");
        } catch(const json::out_of_range&) {
            charSize = mainMenu["charSize"];
        }

        buttons_.push_back(std::make_unique<gui::Button>(*this, size,
                                                         halfWindow + sf::Vector2f(offset["x"], offset["y"]),
                                                         name, font, charSize, mainMenuFunc.at(name)));
        auto& addedButton = buttons_.back();
        addObserver(addedButton.get());
    }
}

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {
        const auto& backgroundImage = game->getAssetsManager<TextureManager>().getAsset(Textures::BACKGROUND);
        background_.setSize(sf::Vector2f(targetWindow->getSize()));
        background_.setTexture(&backgroundImage);

        initButtons();
}

void MainMenuState::updateFromInput(const float dt) {
    checkForGameQuit();
    updateMousePos();

    for(auto& button : buttons_) {
        button->update(mouseWindowPos_);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for(const auto& observer : observers_) {
            observer->onNotify(Event::MOUSE_LEFT_CLICK, *this);
            if(quitState_) {
                break;
            }
        }
    }
}

void MainMenuState::update(const float dt) {
    State::update(dt);
}

void MainMenuState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Black);

    target->draw(background_);
    for(auto& button : buttons_) {
        button->render(*target);
    }
}

void MainMenuState::cleanup() {
    quitState_ = true;
    observers_.clear();
    game_ = nullptr;
}
