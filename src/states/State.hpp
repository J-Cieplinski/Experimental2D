#pragma once

#include <memory>
#include "SFML/Graphics.hpp"

class State {
    protected:
        std::shared_ptr<sf::RenderWindow> m_targetWindow;
        std::vector<sf::Texture> m_textures;
        bool m_quit = false;

    public:
        State(std::shared_ptr<sf::RenderWindow> targetWindow);
        virtual ~State();

        void checkForExit();
        bool isQuitting() const;

        virtual void updateFromInput(const float dt) = 0;
        virtual void update(const float dt) = 0;
        virtual void render(sf::RenderTarget* target = nullptr) = 0;
        virtual void exitState() = 0;
};