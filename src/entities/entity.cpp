#include "entities/entity.hpp"

using namespace entities;

Entity::Entity(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Entity::~Entity() {
    // Do nothing
}

float Entity::getX() const {
    return this->x;
}

float Entity::getY() const {
    return this->y;
}

float Entity::getWidth() const {
    return this->width;
}

float Entity::getHeight() const {
    return this->height;
}

void Entity::setX(float x) {
    this->x = x;
}

void Entity::setY(float y) {
    this->y = y;
}

void Entity::setWidth(float width) {
    this->width = width;
}

void Entity::setHeight(float height) {
    this->height = height;
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

void Entity::update(Zone *container) {
    // Do nothing
}

void Entity::render(float depth, Zone *container) {
    // Do nothing
}

components::Hurtbox *Entity::getHurtbox() const {
    return nullptr;
}

components::Collider *Entity::getCollider() const {
    return nullptr;
}

components::LifeManager *Entity::getLifeManager() const {
    return nullptr;
}

components::Movement *Entity::getMovement() const {
    return nullptr;
}

components::Animator *Entity::getAnimator() const {
    return nullptr;
}