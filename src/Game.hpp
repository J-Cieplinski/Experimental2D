#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <stack>
#include "util.hpp"

class State;

class Game {
    public:
        void run();
        Game();
        ~Game();

        void changeState(States stateId, std::unique_ptr<State> state = nullptr);
        void pushState(States stateId, std::unique_ptr<State> state = nullptr);
    private:
        std::shared_ptr<sf::RenderWindow> m_window;
        sf::Event m_event;
        sf::Clock m_dtClock;
        float m_dt;

        std::map<States, std::unique_ptr<State>> m_states;
        State* m_currentState;

        void update();
        void updateEvents();
        void updateDt();
        void render();

        void initStates();
        void initWindow();
};