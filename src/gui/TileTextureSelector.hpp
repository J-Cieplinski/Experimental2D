#pragma once
#include "SFML/Graphics.hpp"
#include "Component.hpp"

namespace gui {
    class TileTextureSelector : public Component {
        public:
            TileTextureSelector(State &state, sf::Texture& texture, int x, int y);
            const sf::IntRect& getPickedTile() const;
            bool onNotify(Event event, const State& state) override;
            void render(sf::RenderTarget& target) override;
            void update(const sf::Vector2i& mousePos) override;
        private:
            sf::Texture& texture_;
            sf::Sprite tileSheet_;
            sf::RectangleShape selectorBounds_;
            sf::RectangleShape selectRectangle_;
            const unsigned int gridSize_ {64};
            sf::Sprite pickedTexture_;
            sf::IntRect pickedTile_ {0,0,0,0};

            bool isInBounds(const sf::Vector2i& mousePos);
    };
}