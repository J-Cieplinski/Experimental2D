#pragma once
#include <functional>
#include "../util.hpp"
#include "GuiObserver.hpp"
#include "SFML/Graphics.hpp"


namespace gui {
    class Button : public GuiObserver {
        public:
            Button(sf::Vector2f size, sf::Vector2f position, const std::string& text, sf::Font* font, uint8_t characterSize, std::function<void()> function);
            void onNotify(Event event, const sf::Vector2i& mousePos) override;
            void render(sf::RenderTarget& target);
            void update(const sf::Vector2i& mousePos);
        private:
            sf::RectangleShape buttonArea_;
            sf::Font* font_;
            sf::Text text_;
            std::function<void()> buttonCallback_;

            sf::Color highlightColor_;
            sf::Color normalColor_;

            bool isHovered_ = false;

            bool isHovered(const sf::Vector2i& mousePos);
    };
}