#pragma once
#include "AnimationComponent.hpp"
#include "SFML/Graphics.hpp"

class Entity;
class GraphicsComponent {
    public:
        GraphicsComponent();

        void render(sf::RenderTarget& target);
        void update(const Entity& entity);
        AnimationComponent& getAnimationComponent();
    private:
        sf::Sprite sprite_;
        AnimationComponent animationComponent_;
};