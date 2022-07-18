#include "Button.hpp"
#include "../states/State.hpp"

namespace gui {

    Button::Button(State& state, sf::Vector2f size, sf::Vector2f position, const std::string& text, const sf::Font& font, uint8_t characterSize, std::function<void()> function) :
        Observer(state), font_(font), highlightColor_(sf::Color::White), normalColor_({200, 200, 200, 200}), buttonCallback_(std::move(function))
    {
        buttonArea_.setFillColor(sf::Color::Transparent);
        buttonArea_.setPosition(position);
        buttonArea_.setSize(size);

        text_.setFont(font_);
        text_.setCharacterSize(characterSize);
        text_.setString(text);
        text_.setFillColor(normalColor_);
        text_.setPosition(position.x + (size.x / 2) - (text_.getGlobalBounds().width / 2), position.y + (text_.getGlobalBounds().height / 2));
    }

    bool Button::isHovered(const sf::Vector2i& mousePos) {
        return buttonArea_.getGlobalBounds().contains(sf::Vector2f(mousePos));
    }

    bool Button::onNotify(Event event, const State& state) {
        if(event == Event::MOUSE_CLICK && isHovered(state.getMouseWindowPos())) {
            buttonCallback_();
            return true;
        }
        return false;
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