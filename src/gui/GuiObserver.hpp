#pragma once
#include "SFML/Graphics.hpp"
#include "../util.hpp"

namespace gui {
    class GuiObserver {
        public:
            virtual void onNotify(Event event, const sf::Vector2i& mousePos) = 0;
    };
}