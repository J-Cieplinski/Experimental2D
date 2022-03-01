#include "Button.hpp"

Button::Button()
{
    buttonArea_.setFillColor(sf::Color::Black);
    buttonArea_.setPosition({200,200});
    buttonArea_.setSize({100, 100});
}

void Button::onNotify(Event event, const sf::Vector2f& mousePos) {
    if(event == Event::MOUSE_CLICK && buttonArea_.getGlobalBounds().contains(mousePos)) {
        buttonArea_.setFillColor(buttonArea_.getFillColor() + sf::Color(1,0,1));
    }
}

void Button::render(sf::RenderTarget& target) {
    target.draw(buttonArea_);
}
