#include "List.hpp"

namespace gui {
    List::List(State& state, json& itemList, sf::Font& font, std::map<std::string, std::function<void()>> callbacks)
        : Observer(state)
    {
        const auto listButtonName = itemList["name"];
        const auto charSize = itemList["charSize"];
        const float width = itemList["width"];
        const float height = itemList["height"];
        const auto offset = itemList["centerOffset"];
        sf::Vector2f offsetVector {offset["x"], offset["y"]};
        sf::Vector2f sizeVector {width, height};
        auto buttonFunc = [&]() { isActive_ = true; };

        button_ = std::make_unique<Button>(state, sizeVector, offsetVector, listButtonName, font, charSize, buttonFunc);
        const auto mainButtonPos = button_->buttonArea_.getPosition();

        listItems_.reserve(callbacks.size());
        for(const auto& item : callbacks) {
            //TODO: calculate buttons positions
            auto pos = mainButtonPos;
            listItems_.emplace_back(state, sizeVector, pos, item.first, font, charSize, item.second);
        }
    }

    void List::onNotify(Event event, State& state) {
        if(isActive_) {
            for(auto& item : listItems_) {
                item.onNotify(event, state);
            }
        } else {
            button_->onNotify(event, state);
        }
    }

    void List::render(sf::RenderTarget& target) {
        button_->render(target);
        if(isActive_) {
            for(auto& item : listItems_) {
                item.render(target);
            }
        }
    }

    void List::update(const sf::Vector2i& mousePos) {
        button_->update(mousePos);
        if(isActive_) {
            for(auto& item : listItems_) {
                item.update(mousePos);
            }
        }
    }
}