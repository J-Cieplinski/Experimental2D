#include <fstream>
#include <ostream>
#include "SettingsMenuState.hpp"
#include "../gui/DropdownList.hpp"
#include "../Game.hpp"
#include "MainMenuState.hpp"

SettingsMenuState::SettingsMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {
        auto& font = game_->getAssetsManager<FontsManager>().getAsset(Fonts::MAIN);
        auto& backgroundImage = game_->getAssetsManager<TextureManager>().getAsset(Textures::BACKGROUND);
        background_.setSize(sf::Vector2f(targetWindow->getSize()));
        background_.setTexture(&backgroundImage);

        std::map<std::string, std::function<void()>> settingsMenuFunc;
        settingsMenuFunc["Apply"] = [&]() { };
        settingsMenuFunc["Back"] = [&]() { game_->changeState(States::MENU); };

        const auto halfWindow = sf::Vector2f(targetWindow_->getSize() / 2u);

        std::ifstream buttonsConfigFile("configs/buttons.json");
        assert(buttonsConfigFile.is_open());

        auto buttonsConfig = json::parse(buttonsConfigFile);
        auto settings = buttonsConfig["settings"];
        const auto buttonsAmount = settings["buttons"].size() + settings["lists"].size();
        buttons_.reserve(buttonsAmount);

        for(auto& button : settings["buttons"]) {
            auto size = sf::Vector2f(button["width"], button["height"]);
            auto offset = button["centerOffset"];
            std::string name = button["name"];

            uint8_t charSize {0};

            try {
                charSize = button.at("charSize");
            } catch(const json::out_of_range& e) {
                charSize = settings["charSize"];
            }

            buttons_.push_back(std::make_unique<gui::Button>(*this, size, halfWindow + sf::Vector2f(offset["x"], offset["y"]), name, font, charSize, settingsMenuFunc.at(name)));
         }

        for(auto& listItem : settings["lists"]) {
            std::string name = listItem["name"];

            std::map<std::string, std::function<void()>> funcs;

            const auto title = game->getTitle();
            for(auto& option : listItem["options"]) {
                int width = option["width"];
                int height = option["height"];
                funcs[option["name"]] = [=]() {
                    std::ifstream appConfigFile("configs/window.json");
                    assert(appConfigFile.is_open());

                    auto appConfig = json::parse(appConfigFile);

                    appConfig["window"]["width"] = width;
                    appConfig["window"]["height"] = height;

                    std::ofstream appConfigOutput("configs/window.json");
                    assert(appConfigOutput.is_open());
                    appConfigOutput << std::setw(4) << appConfig;
                };
            }

            buttons_.push_back(std::make_unique<gui::DropdownList>(*this, listItem, font, funcs));
        }
        for(auto& button : buttons_) {
            addObserver(button.get());
        }
}

void SettingsMenuState::updateFromInput(const float dt) {
    checkForGameQuit();

    if(game_->event_.type == sf::Event::MouseMoved) {
        updateMousePos();

        for(auto& button : buttons_) {
            button->update(mouseWindowPos_);
        }
    }

    if(game_->event_.type == sf::Event::MouseButtonReleased &&
        game_->event_.mouseButton.button == sf::Mouse::Button::Left) {
        for(const auto& observer : observers_) {
            observer->onNotify(Event::MOUSE_CLICK, *this);
            if(quitState_) {
                break;
            }
        }
    }
}

void SettingsMenuState::update(const float dt) {
    State::update(dt);
}

void SettingsMenuState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Black);

    target->draw(background_);
    for(auto& button : buttons_) {
        button->render(*target);
    }
}

void SettingsMenuState::cleanup() {
    quitState_ = true;
}
