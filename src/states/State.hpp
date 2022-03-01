#pragma once

#include <memory>
#include <set>
#include "SFML/Graphics.hpp"
#include "../gui/Button.hpp"

class Game;
class State {
    protected:
        Game* game_;
        std::shared_ptr<sf::RenderWindow> targetWindow_;
        std::vector<sf::Texture> m_textures;
        std::map<std::string, sf::Keyboard::Key> keybinds_;
        sf::Vector2i mouseWindowPos_;
        sf::Vector2i mouseScreenPos_;
        sf::Vector2f mouseViewPos_;
        std::set<gui::Button*> observers_;

        bool quit_ = false;
        bool paused_ = false;

        void initKeybinds(const char* configFile);
    public:
        State(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game, const char* keybindsConfig = "configs/generalKeybinds.json");
        virtual ~State();

        void checkForGameQuit();
        bool isQuitting() const;
        bool isPaused() const;
        void unpause();
        void pause();
        void updateMousePos();
        void addObserver(gui::Button* button);
        void removeObserver(gui::Button* button);

        virtual void updateFromInput(const float dt) = 0;
        virtual void update(const float dt) = 0;
        virtual void render(sf::RenderTarget* target = nullptr) = 0;
        virtual void cleanup() = 0;

};