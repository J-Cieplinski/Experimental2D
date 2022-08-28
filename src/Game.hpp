#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <stack>
#include "util.hpp"
#include "AssetsManager.hpp"

class State;
using TextureManager = AssetsManager<Textures, sf::Texture>;
using FontsManager = AssetsManager<Fonts, sf::Font>;

class Game {
    public:
        void run();
        Game();
        ~Game();

        void changeState(States stateId);
        void pushState(States stateId);
        void quitState(States stateId);
        void pauseAllStates();
        const std::string& getTitle() const;
        template <typename Type>
        Type& getAssetsManager();

        sf::Event event_;
    private:
        std::shared_ptr<sf::RenderWindow> window_;
        sf::Clock dtClock_;
        float dt_;

        std::map<States, std::unique_ptr<State>> states_;
        State* currentState_;
        TextureManager textureManager_;
        FontsManager fontsManager_;

        std::string title_;

        void update();
        void updateEvents();
        void updateDt();
        void render();

        void initStates();
        void initWindow();
        void initResources();

        void switchState(States stateId);

        std::unique_ptr<State> createState(States state);
};