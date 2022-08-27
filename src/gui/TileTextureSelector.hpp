#pragma once
#include "SFML/Graphics.hpp"
#include "Component.hpp"

namespace gui {
    class TileTextureSelector : public Component {
        public:
            TileTextureSelector(State &state, sf::Texture& texture, int x, int y);
            bool onNotify(Event event, const State& state) override;
            void render(sf::RenderTarget& target) override;
            void update(const sf::Vector2i& mousePos) override;
        private:
            sf::Texture& texture_;
            sf::Sprite tileSheet_;
            sf::RectangleShape selectorBounds_;

    };
}