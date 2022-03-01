#include <memory>
#include <cassert>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "../Game.hpp"
#include "../util.hpp"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game) {

        font_ = std::make_unique<sf::Font>();
        assert(font_->loadFromFile("assets/fonts/LeagueGothic.ttf"));
        testButton_ = std::make_unique<gui::Button>(sf::Vector2f(100.f, 50.f), sf::Vector2f(100.f, 100.f), "Test Button", font_.get(), 25);
        addObserver(testButton_.get());
}

void MainMenuState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["CONFIRM"])) {
        game_->pushState(States::GAME, std::make_unique<GameState>(targetWindow_, game_));
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

    if(game_->event_.type == sf::Event::MouseMoved) {
        updateMousePos();
        testButton_->update(mouseWindowPos_);
    }

    updateFromInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Cyan);
    testButton_->render(*target);
}

void MainMenuState::cleanup() {
    game_ = nullptr;
}
