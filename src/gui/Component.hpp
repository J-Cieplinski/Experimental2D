#pragma once

#include "../Observer.hpp"

namespace sf {
    class RenderTarget;
}

namespace gui {
    class Component : public Observer {
        public:
            Component(State& state) : Observer(state) {

            }
            virtual void render(sf::RenderTarget& target) = 0;
            virtual void update(const sf::Vector2i& mousePos) = 0;
    };

}

