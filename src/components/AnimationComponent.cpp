#include "AnimationComponent.hpp"
AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& textureSheet,
                                        int frameWidth, int frameHeight, float animationTime,
                                        int framesX, int framesY, int startFrameX, int startFrameY)
    : textureSheet_(textureSheet), sprite_(sprite), frameHeight_(frameHeight), frameWidth_(frameWidth), animationTime_(animationTime),
        firstFrame_{startFrameX * frameWidth, startFrameY * frameHeight, frameWidth, frameHeight}, lastFrame_{framesX * frameWidth, framesY * frameHeight, frameWidth, frameHeight}, currentFrame_{firstFrame_}
{
    sprite_.setTexture(textureSheet_, true);
    sprite_.setTextureRect(currentFrame_);
}

void AnimationComponent::Animation::play(const float dt) {
    timer_ += 100 * dt;

    if(timer_ >= animationTime_) {
        timer_ = 0;

        if(currentFrame_ == lastFrame_) {
            currentFrame_.left = firstFrame_.left;
        } else {
            currentFrame_.left += frameWidth_;
        }

        sprite_.setTextureRect(currentFrame_);
    }
}

void AnimationComponent::Animation::reset() {
    currentFrame_ = firstFrame_;
}

void AnimationComponent::play(const std::string& key, const float dt) {
    animations_[key]->play(dt);
}

void AnimationComponent::addAnimation(const std::string& key, sf::Texture textureSheet, int frameWidth, int frameHeight, float animationTime,
                                        int framesX, int framesY, int startFrameX, int startFrameY) {
    animations_[key] = std::make_shared<Animation>(sprite_, textureSheet, frameWidth, frameHeight, animationTime, framesX, framesY, startFrameX, startFrameY);
}
