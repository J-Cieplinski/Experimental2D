#include "DropdownList.hpp"

namespace gui {
    DropdownList::DropdownList(State& state, json& itemList, sf::Font& font, std::map<std::string, std::function<void()>> callbacks) :
    Button(state, sf::Vector2f(itemList["width"], itemList["height"]), sf::Vector2f(itemList["centerOffset"]["x"],itemList["centerOffset"]["y"]), itemList["name"], font, itemList["charSize"], [&]() { isActive_ = !isActive_; }) {
        const auto charSize = itemList["charSize"];
        const float width = itemList["width"];
        const float height = itemList["height"];
        sf::Vector2f sizeVector {width, height};
        const auto mainButtonPos = buttonArea_.getPosition();

        auto numberOfButtons = callbacks.size();
        listItems_.reserve(numberOfButtons);
        auto counter = numberOfButtons / 2.f;
        for(const auto& item : callbacks) {
            auto pos = mainButtonPos + sf::Vector2f{200, height * counter--};
            auto& button = listItems_.emplace_back(state, sizeVector, pos, item.first, font, charSize, item.second);
        }
    }

    DropdownList::~DropdownList() {
        isActive_ = false;
    }

    bool DropdownList::onNotify(Event event, const State& state) {
        bool wasProcessed = false;
        if(isActive_) {
            for(auto& item : listItems_) {
                if(wasProcessed = item.onNotify(event, state)) {
                    isActive_ = false;
                    break;
                }
            }
        }
        return wasProcessed || Button::onNotify(event, state);
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