#include "EntityControlComponent.hpp"
#include "../entities/Entity.hpp"


void EntityControlComponent::update(Entity& target) {

}

MovementState EntityControlComponent::getState() {
    return state_;
}
