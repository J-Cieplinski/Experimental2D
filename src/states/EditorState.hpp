#pragma once

#include "State.hpp"
#include "../map/TileMap.hpp"

namespace gui {
    class Component;
    class Button;
    class TileTextureSelector;
}

class EditorState : public State {
    public:
        EditorState(std::shared_ptr<sf::RenderWindow> targetWindow, Game* game);

        void updateFromInput(const float dt) override;
        void update(const float dt) override;
        void render(sf::RenderTarget* target = nullptr) override;
        void cleanup() override;
    private:
        std::vector<std::shared_ptr<gui::Component>> guiElements_;
        std::shared_ptr<gui::TileTextureSelector> tilesSelector_;
        TileMap map_;
        sf::View mapTilesView_;
        std::map<int, MapLayer> layers_;
        MapLayer activeLayer_;

        void notifyObservers(Event event);
        void placeTile();
};