#include "components/hitbox.hpp"
#include <citro2d.h>
#include "utils/constants.hpp"
#include "utils/utilities.hpp"
#include "entities/zone.hpp"

using namespace components;

Hitbox::Hitbox(u8 scan, u8 damage, float x, float y, float width, float height) {
    this->scan = scan;
    this->damage = damage;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Hitbox::~Hitbox() {
    // Do nothing
}

void Hitbox::render(entities::Entity *parent, float depth, entities::Zone *container) {
#ifdef LYNCHY_DEBUG
    C2D_DrawRectSolid(
        parent->getX() + this->x + container->getX(), parent->getY() + this->y + container->getY(),
        Z_INDEX_UI,
        this->width, this->height,
        DEBUG_HITBOX_COLOR()
    );
#endif
}

void Hitbox::checkHurtbox(entities::Entity *parent, entities::Zone *container, entities::Entity *other, entities::Zone *other_container) {
    Hurtbox *hurtbox = other->getHurtbox();
    LifeManager *life_manager = other->getLifeManager();
    if (!hurtbox || !life_manager || !(this->scan & hurtbox->getVisible()))
        return;
    
    float parent_x = this->x + parent->getX() + container->getX();
    float parent_y = this->y + parent->getY() + container->getY();
    float other_x = hurtbox->getX() + other->getX() + other_container->getX();
    float other_y = hurtbox->getY() + other->getY() + other_container->getY();

    if (!(
        parent_x + this->width <= other_x ||
        parent_x >= other_x + hurtbox->getWidth() ||
        parent_y + this->height <= other_y ||
        parent_y >= other_y + hurtbox->getHeight()
    )) {
        life_manager->takeDamage(this->damage);
    }
}

void Hitbox::setDamage(u8 damage) {
    this->damage = damage;
}

void Hitbox::setWidth(float width) {
    this->width = width;
}

void Hitbox::setHeight(float height) {
    this->height = height;
}