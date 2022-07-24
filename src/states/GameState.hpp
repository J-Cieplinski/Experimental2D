#pragma once
#include "State.hpp"
#include "../entities/Entity.hpp"
#include "../map/TileMap.hpp"

class GameState : public State {
    public:
        GameState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(const float dt) override;
        void update(const float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;
    private:
        Entity player_;
        TileMap map_;

        void initPlayer();
};