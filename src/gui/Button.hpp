#pragma once
#include "../util.hpp"
#include "SFML/Graphics.hpp"

class Button {
    public:
        Button();
        void onNotify(Event event, const sf::Vector2f& mousePos);
        void render(sf::RenderTarget& target);
    private:
        sf::RectangleShape buttonArea_;
};