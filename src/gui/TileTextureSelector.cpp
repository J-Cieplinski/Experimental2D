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
    }

    void TileTextureSelector::render(sf::RenderTarget &target) {
        target.draw(selectorBounds_);
        target.draw(tileSheet_);
    }

    bool TileTextureSelector::onNotify(Event event, const State &state) {
        return false;
    }

    void TileTextureSelector::update(const sf::Vector2i &mousePos) {

    }
}