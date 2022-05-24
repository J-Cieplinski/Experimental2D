#pragma once
#include <map>
#include <string>
#include "SFML/Graphics.hpp"

class Entity;
class AnimationComponent {
    private:
        class Animation {
            public:
                Animation(sf::Sprite& sprite, int frameWidth, int frameHeight,
                            float animationTime, int framesX, int framesY, int startFrameX, int startFrameY);

                void play(const float dt);
                void pause();
                void reset();

            sf::Sprite& sprite_;
            sf::IntRect firstFrame_;
            sf::IntRect lastFrame_;
            sf::IntRect currentFrame_;
            float animationTime_;
            float timer_ {0};
            int frameWidth_;
            int frameHeight_;
        };

        sf::Sprite& sprite_;
        sf::Texture textureSheet_;
        std::map<std::string, std::unique_ptr<Animation>> animations_;

    public:
        AnimationComponent(sf::Sprite& sprite, sf::Texture&& textureSheet);
        AnimationComponent(sf::Sprite& sprite);
        void addTextureSheet(sf::Texture&& textureSheet, const sf::Vector2f& scale = {1, 1});

        void play(const std::string& key, const float dt);
        void addAnimation(const std::string& key, int frameWidth, int frameHeight, float animationTime,
                            int framesX, int framesY, int startFrameX, int startFrameY);
};