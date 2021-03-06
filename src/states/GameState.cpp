#include "GameState.hpp"
#include "MainMenuState.hpp"
#include <cassert>
#include "../util.hpp"
#include "../Game.hpp"
#include "../components/PlayerControlComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/AnimationComponent.hpp"
#include "../map/NormalTile.hpp"

GameState::GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game)
{
    initPlayer();

    //TODO: Testing code
    assert(map_.getTilesTexture().loadFromFile("assets/textures/tiles/tilesheet3.png"));
    TileData data(map_.getTilesTexture());
    data.size = {64, 64};
    data.layer = MapLayer::BACKGROUND;
    data.position = sf::Vector2f(targetWindow_->getSize()) / 2.f;
    data.textureRect = {0, 0, 64, 64};

    Tile* tile = new NormalTile(data);
    map_.addTile(tile);

    data.layer = MapLayer::FOREGROUND;
    data.position = sf::Vector2f(targetWindow_->getSize()) / 2.f + sf::Vector2f{64, 0};
    data.textureRect = {0, 64, 64, 64};

    tile = new NormalTile(data);
    map_.addTile(tile);
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
    map_.render(*target);
    player_.render(*target);
    map_.defferedRender(*target);
}

void GameState::cleanup() {
    game_ = nullptr;
}

void GameState::initPlayer() {
    sf::Texture pcTexture;
    assert(pcTexture.loadFromFile("assets/textures/characters/PC/Template_Male.png"));

    auto playerGraphics = new GraphicsComponent();
    auto& animComponent = playerGraphics->getAnimationComponent();
    animComponent.addTextureSheet(std::move(pcTexture), {2, 2});

    animComponent.addAnimation(EntityState::IDLE, 128, 128, 5, 0, 0, 0, 0);
    animComponent.addAnimation(EntityState::MOVING_RIGHT, 128, 128, 16, 3, 0, 0, 2);
    animComponent.addAnimation(EntityState::MOVING_LEFT, 128, 128, 16, 3, 0, 0, 1);
    animComponent.addAnimation(EntityState::MOVING_UP, 128, 128, 16, 3, 0, 0, 3);
    animComponent.addAnimation(EntityState::MOVING_DOWN, 128, 128, 16, 3, 0, 0, 0);

    player_ = Entity(new PlayerControlComponent(keybinds_), new PhysicsComponent(), playerGraphics);
}
