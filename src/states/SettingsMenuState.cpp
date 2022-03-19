#include <fstream>
#include "SettingsMenuState.hpp"
#include "../gui/DropdownList.hpp"
#include "../Game.hpp"

SettingsMenuState::SettingsMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game, const sf::Texture& backgroundImage, const sf::Font& font)
    : State(targetWindow, game), font_(font), backgroundImage_(backgroundImage) {
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

            buttons_.push_back(std::make_unique<gui::Button>(*this, size, halfWindow + sf::Vector2f(offset["x"], offset["y"]), name, font_, charSize, settingsMenuFunc.at(name)));
         }

        for(auto& listItem : settings["lists"]) {
            auto size = sf::Vector2f(listItem["width"], listItem["height"]);
            auto offset = listItem["centerOffset"];
            std::string name = listItem["name"];

            std::map<std::string, std::function<void()>> funcs;

            for(auto& option : listItem["options"]) {
                funcs[option["name"]] = [&]() {
                    targetWindow_->create(sf::VideoMode(option["width"], option["height"]), game->getTitle());
                };
            }

            //gui::DropdownList item(*this, listItem, font_, funcs);
            buttons_.push_back(std::make_unique<gui::DropdownList>(*this, listItem, font_, funcs));
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
