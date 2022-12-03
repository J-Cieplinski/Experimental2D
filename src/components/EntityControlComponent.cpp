#include "EntityControlComponent.hpp"
#include "../entities/Entity.hpp"


void EntityControlComponent::update(Entity& target) {

}

EntityState EntityControlComponent::getState() const {
    return state_;
}
