#include "Button.hpp"

namespace gui {

    Button::Button(sf::Vector2f size, sf::Vector2f position, const std::string& text, sf::Font* font, uint8_t characterSize) :
        font_(font), highlightColor_(sf::Color::White), normalColor_({200, 200, 200, 200})
    {
        buttonArea_.setFillColor(sf::Color::Transparent);
        buttonArea_.setPosition(position);
        buttonArea_.setSize(size);
        buttonArea_.setOutlineColor(sf::Color::Black);
        buttonArea_.setOutlineThickness(1);

        text_.setFont(*font_);
        text_.setCharacterSize(characterSize);
        text_.setString(text);
        text_.setFillColor(normalColor_);
        text_.setPosition(position.x + (size.x / 2) - (text_.getGlobalBounds().width / 2), position.y + (text_.getGlobalBounds().height / 2) );
    }


    bool Button::isHovered(const sf::Vector2i& mousePos) {
        return buttonArea_.getGlobalBounds().contains(sf::Vector2f(mousePos));
    }

    void Button::onNotify(Event event, const sf::Vector2i& mousePos) {
        if(event == Event::MOUSE_CLICK && isHovered(mousePos)) {
            buttonArea_.setFillColor(buttonArea_.getFillColor() + sf::Color(1,0,1));
        }
    }

    void Button::render(sf::RenderTarget& target) {
        target.draw(buttonArea_);
        target.draw(text_);
    }

    void Button::update(const sf::Vector2i& mousePos) {
        isHovered_ = isHovered(mousePos);

        if(isHovered_) {
            text_.setFillColor(highlightColor_);
        } else {
            text_.setFillColor(normalColor_);
        }
    }

}