#include "EditorState.hpp"
#include "MainMenuState.hpp"
#include "../gui/TileTextureSelector.hpp"


EditorState::EditorState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game)
    : State(targetWindow, game, "configs/editorKeybinds.json"),
    map_(game_->getAssetsManager<TextureManager>())
{
    map_.loadMap(targetWindow_->getSize().x, targetWindow_->getSize().y);
    tilesSelector_ = std::make_shared<gui::TileTextureSelector>(*this, map_.getTilesTexture(),0,0);
    guiElements_.push_back(tilesSelector_);
    addObserver(tilesSelector_.get());
    mapTilesView_.setSize(200,200);
}

void EditorState::updateFromInput(const float dt) {
    checkForGameQuit();
    if(sf::Keyboard::isKeyPressed(keybinds_["BACK"])) {
        game_->pushState(States::MENU);
    }
    if(sf::Keyboard::isKeyPressed(keybinds_["SAVE"])) {
        map_.saveMap();
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        placeTile();
    }
}

void EditorState::update(const float dt) {
    updateMousePos();
    updateFromInput(dt);

    for(auto& button : guiElements_) {
        button->update(mouseWindowPos_);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        notifyObservers(Event::MOUSE_LEFT_CLICK);
    } else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        notifyObservers(Event::MOUSE_RIGHT_CLICK);
    }
}

void EditorState::cleanup() {
    quitState_ = true;
    observers_.clear();
    guiElements_.clear();
    game_ = nullptr;
}

void EditorState::render(sf::RenderTarget* target) {
    target = target ? target : targetWindow_.get();
    target->clear(sf::Color::Red);

    map_.render(*target);
    map_.defferedRender(*target);

    for(auto& button : guiElements_) {
        button->render(*target);
    }
}

void EditorState::notifyObservers(Event event) {
    for(const auto& observer : observers_) {
        observer->onNotify(event, *this);
        if(quitState_) {
            break;
        }
    }
}

void EditorState::placeTile() {
    auto pickedTile = tilesSelector_->getPickedTile();
    if(pickedTile == sf::IntRect(0, 0, 0, 0)) {
        return;
    }

    auto mousePos = getMouseWindowPos();
    int x = mousePos.x / 64 * 64;
    int y = mousePos.y / 64 * 64;

    TileData data(map_.getTilesTexture());
    data.size = {64, 64};
    data.layer = MapLayer::BACKGROUND;
    data.position.x = x;
    data.position.y = y;
    data.textureRect = pickedTile;
    map_.addTile(data);
}
