#include "components/life.hpp"

using namespace components;

LifeManager::LifeManager(u8 life, u8 max_life, u16 invicible_time) {
    this->actual_life = life;
    this->max_life = max_life;

    this->timer = new Timer(invicible_time, false);
    this->timer->setFinished();
}

LifeManager::~LifeManager() {
    delete this->timer;
}

void LifeManager::update(entities::Entity *parent, entities::Zone *container) {
    this->timer->update(parent, container);
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
    if (!this->timer->isFinished())
        return;

    this->actual_life = damage >= this->actual_life ? 0 : this->actual_life - damage;
    this->timer->reset();
}

void LifeManager::addLife(u8 life) {
    if (life >= this->max_life - this->actual_life) {
        this->actual_life = this->max_life;
        return;
    }

    this->actual_life += life;
}

bool LifeManager::isDead() const {
    return this->actual_life == 0;
}