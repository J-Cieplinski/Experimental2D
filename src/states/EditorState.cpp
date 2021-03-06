#include "EditorState.hpp"
#include "MainMenuState.hpp"
#include "../Game.hpp"
#include "../gui/Button.hpp"


EditorState::EditorState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game, "configs/editorKeybinds.json")
{

}

void EditorState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["BACK"])) {
        game_->pushState(States::MENU, std::make_unique<MainMenuState>(targetWindow_, game_));
    }
}

void EditorState::update(const float dt) {
    updateMousePos();
    updateFromInput(dt);

    for(auto& button : buttons_) {
        button.update(mouseWindowPos_);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for(const auto& observer : observers_) {
            observer->onNotify(Event::MOUSE_CLICK, *this);
            if(quitState_) {
                break;
            }
        }
    }
}

void EditorState::cleanup() {
    quitState_ = true;
    observers_.clear();
    game_ = nullptr;
}

void EditorState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Black);

    for(auto& button : buttons_) {
        button.render(*target);
    }
}
