#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "../Game.hpp"
#include "../components/PlayerControlComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/PhysicsComponent.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game), player_(new PlayerControlComponent(keybinds_), new PhysicsComponent(), new GraphicsComponent())
{

}

void GameState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["BACK"])) {
        game_->pushState(States::PAUSED, std::make_unique<MainMenuState>(targetWindow_, game_));
    }
}

void GameState::update(const float dt) {
    State::update(dt);
    player_.update(dt);
}

void GameState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Red);
    player_.render(*target);
}

void GameState::cleanup() {
    game_ = nullptr;
}
