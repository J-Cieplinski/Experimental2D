#pragma once

#include <memory>
#include "SFML/Graphics.hpp"

class Game;
class State {
    protected:
        std::shared_ptr<sf::RenderWindow> m_targetWindow;
        Game* m_game;
        std::vector<sf::Texture> m_textures;
        bool m_quit = false;
        bool m_paused = false;

    public:
        State(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);
        virtual ~State();

        void checkForExit();
        bool isQuitting() const;
        bool isPaused() const;
        void unpause();
        void pause();

        virtual void updateFromInput(const float dt) = 0;
        virtual void update(const float dt) = 0;
        virtual void render(sf::RenderTarget* target = nullptr) = 0;
        virtual void cleanup() = 0;
};