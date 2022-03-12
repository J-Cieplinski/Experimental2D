#pragma once
#include "Button.hpp"
#include "../../dependencies/nlohmann/json.hpp"
#include <vector>
#include <memory>
#include <map>

using json = nlohmann::json;

namespace gui {
    class DropdownList : public Observer {
        public:
            DropdownList(State& state, json& itemList, sf::Font& font, std::map<std::string, std::function<void()>> callbacks);
            void onNotify(Event event, State& state) override;
            void render(sf::RenderTarget& target);
            void update(const sf::Vector2i& mousePos);
        private:
            std::unique_ptr<Button> button_;
            std::vector<Button> listItems_;
            bool isActive_ {false};
    };
}