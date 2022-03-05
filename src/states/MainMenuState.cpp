#include <memory>
#include <cassert>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "../Game.hpp"
#include "../util.hpp"

void MainMenuState::initButtons() {
    auto startFun = [&]() {
        game_->pushState(States::GAME, std::make_unique<GameState>(targetWindow_, game_));
    };
    auto settingsFun = [&]() {

    };
    auto exitFun = [&]() {
        quit_ = true;
    };

    auto halfWindow = sf::Vector2f(targetWindow_->getSize() / 2u);
    auto size = sf::Vector2f(150.f, 50.f);

    buttons_.push_back({size, halfWindow + sf::Vector2f(-size.x / 2, -size.y), "Start", font_.get(), 25, startFun});
    buttons_.push_back({size, halfWindow + sf::Vector2f(-size.x / 2, 0), "Settings", font_.get(), 25, settingsFun});
    buttons_.push_back({size, halfWindow + sf::Vector2f(-size.x / 2, + size.y), "Exit", font_.get(), 25, exitFun});

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
