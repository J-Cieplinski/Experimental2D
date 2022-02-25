#pragma once

#include <memory>
#include "SFML/Graphics.hpp"

class Game;
class State {
    protected:
        std::shared_ptr<sf::RenderWindow> targetWindow_;
        Game* game_;
        std::vector<sf::Texture> m_textures;
        bool quit_ = false;
        bool paused_ = false;

    public:
        State(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);
        virtual ~State();

        void checkForGameQuit();
        bool isQuitting() const;
        bool isPaused() const;
        void unpause();
        void pause();

        virtual void updateFromInput(const float dt) = 0;
        virtual void update(const float dt) = 0;
        virtual void render(sf::RenderTarget* target = nullptr) = 0;
        virtual void cleanup() = 0;
};