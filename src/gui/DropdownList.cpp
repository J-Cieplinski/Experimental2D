#include "DropdownList.hpp"

namespace gui {
    DropdownList::DropdownList(State& state, json& itemList, sf::Font& font, std::map<std::string, std::function<void()>> callbacks) :
    Button(state, sf::Vector2f(itemList["width"], itemList["height"]), sf::Vector2f(itemList["centerOffset"]["x"],itemList["centerOffset"]["y"]), itemList["name"], font, itemList["charSize"], [&]() { isActive_ = !isActive_; }) {
        const auto charSize = itemList["charSize"];
        const float width = itemList["width"];
        const float height = itemList["height"];
        sf::Vector2f sizeVector {width, height};
        const auto mainButtonPos = buttonArea_.getPosition();

        listItems_.reserve(callbacks.size());
        for(const auto& item : callbacks) {
            //TODO: calculate buttons positions
            auto pos = mainButtonPos + sf::Vector2f{200, 0};
            auto& button = listItems_.emplace_back(state, sizeVector, pos, item.first, font, charSize, item.second);
        }
    }

    void DropdownList::onNotify(Event event, State& state) {
        if(isActive_) {
            for(auto& item : listItems_) {
                item.onNotify(event, state);
            }
        }
        Button::onNotify(event, state);
    }

    void DropdownList::render(sf::RenderTarget& target) {
        Button::render(target);
        if(isActive_) {
            for(auto& item : listItems_) {
                item.render(target);
            }
        }
    }

    void DropdownList::update(const sf::Vector2i& mousePos) {
        Button::update(mousePos);
        if(isActive_) {
            for(auto& item : listItems_) {
                item.update(mousePos);
            }
        }
    }
}