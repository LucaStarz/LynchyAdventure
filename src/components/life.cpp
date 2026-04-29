#include "systems/game.hpp"
using namespace components;

LifeManager::LifeManager(u8 life, u8 max_life) {
    this->actual_life = life;
    this->max_life = max_life;
    this->invicible_time = 0;
}

LifeManager::~LifeManager() {
    // Do nothing
}

u8 LifeManager::getActualLife() const {
    return this->actual_life;
}

void LifeManager::setActualLife(u8 life) {
    this->actual_life = life;
}

u8 LifeManager::getMaxLife() const {
    return this->max_life;
}

void LifeManager::setMaxLife(u8 max_life) {
    this->max_life = max_life;
}

void LifeManager::takeDamage(u8 damage) {
    if (damage >= this->actual_life) {
        this->actual_life = 0;
        return;
    }

    this->actual_life -= damage;
}

void LifeManager::addLife(u8 life) {
    if (life >= this->max_life - this->actual_life) {
        this->actual_life = this->max_life;
        return;
    }

    this->actual_life += life;
}

bool LifeManager::isInvicible() const {
    return this->invicible_time > 0;
}

void LifeManager::setInvicible(u8 invicible_time) {
    if (!this->invicible_time)
        this->invicible_time = invicible_time;
}