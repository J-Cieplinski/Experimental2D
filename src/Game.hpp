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

        sf::Event event_;
    private:
        std::shared_ptr<sf::RenderWindow> window_;
        sf::Clock dtClock_;
        float dt_;

        std::map<States, std::unique_ptr<State>> states_;
        State* currentState_;

        void update();
        void updateEvents();
        void updateDt();
        void render();

        void initStates();
        void initWindow();
};