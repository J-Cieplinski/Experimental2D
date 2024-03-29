#pragma once
#include "Button.hpp"
#include "../../dependencies/nlohmann/json.hpp"
#include <vector>
#include <memory>
#include <map>

using json = nlohmann::json;

namespace gui {
    class DropdownList : public Button {
        public:
            DropdownList(State& state, json& itemList, sf::Font& font, std::map<std::string, std::function<void()>> callbacks);
            ~DropdownList();
            bool onNotify(Event event, const State& state) override;
            void render(sf::RenderTarget& target) override;
            void update(const sf::Vector2i& mousePos) override;
        private:
            std::vector<Button> listItems_;
            bool isActive_ {false};
    };
}