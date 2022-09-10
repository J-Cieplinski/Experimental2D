#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "../util.hpp"
#include "../Game.hpp"
#include "../components/PlayerControlComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/AnimationComponent.hpp"
#include "../map/NormalTile.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game), map_(game_->getAssetsManager<TextureManager>())
{
    initPlayer();
    map_.loadMap();
}

void GameState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["BACK"])) {
        game_->pushState(States::MENU);
    }
}

void GameState::update(const float dt) {
    State::update(dt);
    player_.update(dt);
}

void GameState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Red);
    map_.render(*target);
    player_.render(*target);
    map_.defferedRender(*target);
}

void GameState::cleanup() {
    game_ = nullptr;
}

void GameState::initPlayer() {
    auto& textureManager = game_->getAssetsManager<TextureManager>();

    auto playerGraphics = new GraphicsComponent();
    auto& animComponent = playerGraphics->getAnimationComponent();
    animComponent.addTextureSheet(textureManager.getAsset(Textures::PLAYER), {2, 2});

    animComponent.addAnimation(EntityState::IDLE, 128, 128, 5, 0, 0, 0, 0);
    animComponent.addAnimation(EntityState::MOVING_RIGHT, 128, 128, 16, 3, 0, 0, 2);
    animComponent.addAnimation(EntityState::MOVING_LEFT, 128, 128, 16, 3, 0, 0, 1);
    animComponent.addAnimation(EntityState::MOVING_UP, 128, 128, 16, 3, 0, 0, 3);
    animComponent.addAnimation(EntityState::MOVING_DOWN, 128, 128, 16, 3, 0, 0, 0);

    player_ = Entity(new PlayerControlComponent(keybinds_), new PhysicsComponent(), playerGraphics);
}
