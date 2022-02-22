#pragma once

#include "SFML/Graphics.hpp"
#include <memory>

class Game {
    public:
        void run();
        Game();
        ~Game() = default;
    private:
        std::unique_ptr<sf::RenderWindow> m_window;
        sf::Event m_event;

    void update();
    void render();
};