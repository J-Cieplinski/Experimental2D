#include "GameState.hpp"
#include "MainMenuState.hpp"
#include <cassert>
#include "../Game.hpp"
#include "../components/PlayerControlComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/AnimationComponent.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game)
{
    sf::Texture playerTextureIdle;
    assert(playerTextureIdle.loadFromFile("assets/textures/characters/PC/_Idle.png"));

    sf::Texture playerTextureRun;
    assert(playerTextureRun.loadFromFile("assets/textures/characters/PC/_Run.png"));

    auto playerGraphics = new GraphicsComponent();
    auto& animComponent = playerGraphics->getAnimationComponent();
    animComponent.addAnimation("IDLE", std::move(playerTextureIdle), 120, 80, 10, 9, 0, 0, 0);
    animComponent.addAnimation("RIGHT", std::move(playerTextureRun), 120, 80, 5, 9, 0, 0, 0);
    player_ = Entity(new PlayerControlComponent(keybinds_), new PhysicsComponent(), playerGraphics);
}

void GameState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["BACK"])) {
        game_->pushState(States::MENU, std::make_unique<MainMenuState>(targetWindow_, game_));
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
