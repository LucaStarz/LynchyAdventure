#include "systems/game.hpp"
using namespace entities;

Weapon::Weapon(float x, float y, float w, float h, u8 damage, u8 scan, u16 duration, u16 spritesheet, u16 sprite_index)
    : Entity(x, y) {
    this->enable = false;

    this->addComponent(
        new components::Hitbox(scan, .0f, .0f, w, h),
        COMP_HITBOX
    );

    this->addComponent(
        new components::ImageComponent(spritesheet, sprite_index, 1.f),
        COMP_IMAGE
    );

    this->addComponent(
        new components::Timer(duration, false),
        COMP_TIMER
    );
}

Weapon::~Weapon() {
    // Do nothing
}

bool Weapon::isEnable() const {
    return this->enable;
}

void Weapon::setEnable() {
    if (this->enable) return;

    this->enable = true;
    ((components::Timer*)this->getComponent(COMP_TIMER))->reset();
}

void Weapon::update(Zone *container) {
    if (this->enable) {
        components::Timer *timer = (components::Timer*)this->getComponent(COMP_TIMER);
        timer->update(this, container);
        if (timer->isFinished())
            this->enable = false;
    }
}

void Weapon::render(float depth, Zone *container) {
    if (this->enable)
        this->getComponent(COMP_IMAGE)->render(this, depth, container);
}