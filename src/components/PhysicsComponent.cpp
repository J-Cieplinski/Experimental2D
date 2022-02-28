#include "PhysicsComponent.hpp"
#include "../util.hpp"

void PhysicsComponent::update(float dt, Entity& target) {
    if (length(target.direction_) > 0) {
        velocity_ = lerp(velocity_, normalize(target.direction_) * speed_, acceleration_);
    } else {
        velocity_ = lerp(velocity_, {0, 0}, friction_);
    }
    target.position_ += velocity_ * dt;
}
