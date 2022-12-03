#include "AnimationComponent.hpp"
#include "../util.hpp"

AnimationComponent::Animation::Animation(sf::Sprite& sprite,
                                        int frameWidth, int frameHeight, float animationTime,
                                        int framesX, int framesY, int startFrameX, int startFrameY)
    : sprite_(sprite),
        firstFrame_{startFrameX * frameWidth, startFrameY * frameHeight, frameWidth, frameHeight},
        lastFrame_{((framesX ? framesX : 1) - 1) * frameWidth, (framesY + startFrameY) * frameHeight, frameWidth, frameHeight}, currentFrame_{firstFrame_},
        animationTime_(animationTime),
        frameWidth_(frameWidth),
        frameHeight_(frameHeight)
{
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

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture&& textureSheet)
    : sprite_(sprite), textureSheet_(textureSheet) {

}

AnimationComponent::AnimationComponent(sf::Sprite& sprite)
    : sprite_(sprite) {

}

void AnimationComponent::addTextureSheet(sf::Texture& textureSheet, const sf::Vector2f& scale) {
    textureSheet_ = textureSheet;
    sprite_.setTexture(textureSheet_, true);
    sprite_.setScale(scale);
}

void AnimationComponent::play(EntityState key, const float dt) {
    if(!animations_[key]) {
        return;
    }
    animations_[key]->play(dt);
}

void AnimationComponent::addAnimation(EntityState key, int frameWidth, int frameHeight, float animationTime,
                                        int framesX, int framesY, int startFrameX, int startFrameY) {
        animations_[key] = std::make_unique<Animation>(sprite_, frameWidth, frameHeight, animationTime, framesX, framesY, startFrameX, startFrameY);
}
