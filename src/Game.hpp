#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <stack>

class State;

class Game {
    public:
        void run();
        Game();
        ~Game();
    private:
        std::shared_ptr<sf::RenderWindow> m_window;
        sf::Event m_event;
        sf::Clock m_dtClock;
        float m_dt;

        std::stack<std::unique_ptr<State>> m_states;

        void update();
        void updateEvents();
        void updateDt();
        void render();

        void initStates();
        void initWindow();
};