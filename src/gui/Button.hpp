#pragma once
#include <functional>
#include "../util.hpp"
#include "../Observer.hpp"
#include "SFML/Graphics.hpp"


namespace gui {
    class Button : public Observer {
        public:
            friend class DropdownList;
            Button(State& state, sf::Vector2f size, sf::Vector2f position, const std::string& text, const sf::Font& font, uint8_t characterSize, std::function<void()> function);

            virtual bool onNotify(Event event, const State& state) override;
            virtual void render(sf::RenderTarget& target);
            virtual void update(const sf::Vector2i& mousePos);
        private:
            sf::RectangleShape buttonArea_;
            const sf::Font& font_;
            sf::Text text_;
            std::function<void()> buttonCallback_;

            sf::Color highlightColor_;
            sf::Color normalColor_;

            bool isHovered_ = false;

            bool isHovered(const sf::Vector2i& mousePos);
    };
}