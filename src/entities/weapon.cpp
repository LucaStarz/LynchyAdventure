#include "entities/weapon.hpp"
#include "systems/zone_system.hpp"
#include "utils/utilities.hpp"

using namespace entities;

Weapon::Weapon(float x, float y, float w, float h, u8 damage, u8 scan, u8 visible, u16 duration)
    : Entity(x, y, w, h) {
    this->enable = false;
    this->direction = utils::FIX_DIR_BOTTOM;

    this->hitbox = new components::Hitbox(scan, 1, 0.f, 0.f, w, h);
    this->collider = new components::Collider(visible, scan, 0.f, 0.f, w, h);
    this->image = new components::ImageComponent(utils::SPRT_EMPTY, 0);
    this->timer = new components::Timer(duration, false);
}

Weapon::~Weapon() {
    delete this->image;
    delete this->timer;
    delete this->hitbox;
    delete this->collider;
}

bool Weapon::isEnable() const {
    return this->enable;
}

void Weapon::setEnable() {
    if (this->enable) return;

    this->enable = true;
    this->timer->reset();
}

void Weapon::setDisable() {
    this->enable = false;
    this->timer->setFinished();
}

bool Weapon::update(Zone *container) {
    if (this->enable) {
        this->timer->update(this, container);
        if (this->timer->isFinished())
            this->enable = false;
        
        systems::ZoneSystem &zone_system = systems::ZoneSystem::getInstance();
        this->checkHurtbox(container, zone_system.getActualZone());
        this->checkHurtbox(container, zone_system.getLeftZone());
        this->checkHurtbox(container, zone_system.getTopZone());
        this->checkHurtbox(container, zone_system.getRightZone());
        this->checkHurtbox(container, zone_system.getBottomZone());
    }

    return true;
}

void Weapon::render(float depth, Zone *container) {
    if (this->enable) {
        this->image->render(this, depth, container);
    
    #ifdef LYNCHY_DEBUG
        this->hitbox->render(this, depth, container);
    #endif
    }
}

components::Collider *Weapon::getCollider() const {
    return this->collider;
}

void Weapon::setSpritesheet(utils::SPRITESHEETS_ID spritesheet) {
    this->image->setSpritesheetId(spritesheet);
}

void Weapon::setDamage(u8 damage) {
    this->hitbox->setDamage(damage);
}

void Weapon::setDuration(u16 duration) {
    this->timer->setDuration(duration);
}

void Weapon::setDirectionInfo(u8 direction, float offset_x, float offset_y, float width, float height) {
    this->directions[direction].offset_x = offset_x;
    this->directions[direction].offset_y = offset_y;
    this->directions[direction].width = width;
    this->directions[direction].height = height;
}

void Weapon::updateDirection(entities::Entity *parent, components::Animator *animator) {
    this->direction = animator->getDirection();

    this->setWidth(this->directions[this->direction].width);
    this->setHeight(this->directions[this->direction].height);
    this->hitbox->setWidth(this->directions[this->direction].width);
    this->hitbox->setHeight(this->directions[this->direction].height);
    this->collider->setWidth(this->directions[this->direction].width);
    this->collider->setHeight(this->directions[this->direction].height);

    this->image->setSpriteIndex(this->direction + 1);
    this->setX(parent->getX() + this->directions[this->direction].offset_x + this->direction == utils::FIX_DIR_RIGHT ? parent->getWidth() : 0.f);
    this->setY(parent->getY() + this->directions[this->direction].offset_y + this->direction == utils::FIX_DIR_BOTTOM ? parent->getY() : 0.f);
}

utils::SPRITESHEETS_ID Weapon::getSpritesheet() const {
    return this->image->getSpritesheetId();
}

void Weapon::checkParentInfo(entities::Entity *parent) {
    components::Animator *animator = parent->getAnimator();
    if (!animator)
        return;
    
    if (animator->getDirection() != this->direction)
        this->updateDirection(parent, animator);

    this->setX(parent->getX() + this->directions[this->direction].offset_x + (this->direction == utils::FIX_DIR_RIGHT ? parent->getWidth() : 0.f));
    this->setY(parent->getY() + this->directions[this->direction].offset_y + (this->direction == utils::FIX_DIR_BOTTOM ? parent->getHeight() : 0.f));
}

void Weapon::checkHurtbox(Zone *container, Zone *other_container) {
    for (Entity *entity : other_container->getComplexEntities())
        this->hitbox->checkHurtbox(this, container, entity, other_container);
}