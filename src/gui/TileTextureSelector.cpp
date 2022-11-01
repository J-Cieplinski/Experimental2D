#include "TileTextureSelector.hpp"

namespace gui {
    TileTextureSelector::TileTextureSelector(State &state, sf::Texture &texture, int x, int y)
            : Component(state), texture_(texture) {
        selectorBounds_.setSize({400, 400});
        selectorBounds_.setPosition(x, y);
        selectorBounds_.setOutlineColor(sf::Color::Black);
        selectorBounds_.setOutlineThickness(1);

        tileSheet_.setTexture(texture_);
        if(tileSheet_.getGlobalBounds().width > selectorBounds_.getGlobalBounds().width) {
            tileSheet_.setTextureRect({0,0,
                                       static_cast<int>(selectorBounds_.getGlobalBounds().width),
                                       static_cast<int>(tileSheet_.getGlobalBounds().height)});
        }
        if(tileSheet_.getGlobalBounds().height > selectorBounds_.getGlobalBounds().height) {
            tileSheet_.setTextureRect({0,0,
                                       static_cast<int>(tileSheet_.getGlobalBounds().width),
                                       static_cast<int>(selectorBounds_.getGlobalBounds().height)});
        }
        tileSheet_.setPosition(x, y);

        selectRectangle_.setSize({static_cast<float>(gridSize_), static_cast<float>(gridSize_)});
        selectRectangle_.setPosition(0, 0);
        selectRectangle_.setOutlineColor(sf::Color::Black);
        selectRectangle_.setFillColor(sf::Color::Transparent);
        selectRectangle_.setOutlineThickness(2);

        pickedTexture_.setTexture(texture_);
        pickedTexture_.setTextureRect({static_cast<int>(-gridSize_),static_cast<int>(-gridSize_), 64, 64});
        pickedTexture_.setColor(sf::Color::Transparent);
    }

    void TileTextureSelector::render(sf::RenderTarget &target) {
        target.draw(selectorBounds_);
        target.draw(tileSheet_);
        target.draw(selectRectangle_);
        target.draw(pickedTexture_);
    }

    bool TileTextureSelector::onNotify(Event event, const State &state) {
        switch (event) {
            case Event::MOUSE_LEFT_CLICK:
                if(isInBounds(state.getMouseWindowPos())) {
                    int x = selectRectangle_.getPosition().x;
                    int y = selectRectangle_.getPosition().y;
                    pickedTile_ = {x,y, static_cast<int>(gridSize_), static_cast<int>(gridSize_)};
                    pickedTexture_.setPosition(x, y);
                    pickedTexture_.setColor(sf::Color::White);
                    pickedTexture_.setTextureRect(pickedTile_);
                }
                return true;
            case Event::MOUSE_RIGHT_CLICK:
                pickedTexture_.setColor(sf::Color::Transparent);
                pickedTile_ = {0,0,0,0};
                pickedTexture_.setTextureRect(pickedTile_);
                return true;
        }

        return false;
    }

    void TileTextureSelector::update(const sf::Vector2i &mousePos) {
        int x = mousePos.x / gridSize_ * gridSize_;
        int y = mousePos.y / gridSize_ * gridSize_;
        if(isInBounds(mousePos))
        {
            selectRectangle_.setPosition(x, y);
        }
        pickedTexture_.setPosition(x, y);
    }

    bool TileTextureSelector::isInBounds(const sf::Vector2i &mousePos) {
        return selectorBounds_.getGlobalBounds().contains(sf::Vector2f(mousePos));
    }

    const sf::IntRect &TileTextureSelector::getPickedTile() const {
        return pickedTile_;
    }
}