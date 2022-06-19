#include "GameState.hpp"
#include "MainMenuState.hpp"
#include <cassert>
#include "../util.hpp"
#include "../Game.hpp"
#include "../components/PlayerControlComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/AnimationComponent.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game)
{
    initPlayer();
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

void GameState::initPlayer() {
    sf::Texture pcTexture;
    assert(pcTexture.loadFromFile("assets/textures/characters/PC/PC1.png"));

    auto playerGraphics = new GraphicsComponent();
    auto& animComponent = playerGraphics->getAnimationComponent();
    animComponent.addTextureSheet(std::move(pcTexture), {2, 2});

    animComponent.addAnimation(EntityState::IDLE, 120, 80, 10, 9, 2, 0, 2);
    animComponent.addAnimation(EntityState::MOVING_RIGHT, 120, 80, 10, 9, 1, 0, 1);
    animComponent.addAnimation(EntityState::MOVING_LEFT, 120, 80, 10, 9, 0, 0, 0);

    player_ = Entity(new PlayerControlComponent(keybinds_), new PhysicsComponent(), playerGraphics);
}
