#include "systems/game.hpp"
using namespace entities;

Entity::Entity(float x, float y) {
    this->x = x;
    this->y = y;
}

Entity::~Entity() {
    for (components::Component *component : this->entity_components) {
        if (component) delete component;
    }
}

float Entity::getX() const {
    return this->x;
}

float Entity::getY() const {
    return this->y;
}

void Entity::setX(float x) {
    this->x = x;
}

void Entity::setY(float y) {
    this->y = y;
}

void Entity::moveX(float x) {
    this->x += x;
}

void Entity::moveY(float y) {
    this->y += y;
}

void Entity::moveXY(float x, float y) {
    this->x += x;
    this->y += y;
}

void Entity::addComponent(components::Component *component, u8 component_id) {
    this->entity_components[component_id] = component;
}

components::Component *Entity::getComponent(u8 component_id) const {
    return this->entity_components[component_id];
}

void Entity::update(Zone *container) {
    // Do nothing
}

void Entity::render(float depth, Zone *container) {
    // Do nothing
}