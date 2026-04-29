#include "systems/game.hpp"
using namespace components;

Movement::Movement(float speed) {
    this->speed = speed;
}

Movement::~Movement() {
    // Do nothing
}

void Movement::applyMovement(entities::Entity *parent, entities::Zone *parent_container, u8 direction, float *dx, float *dy) {
    *dx = direction & MOV_DIR_LEFT ? -this->speed
        : direction & MOV_DIR_RIGHT ? this->speed : 0.f;
    
    *dy = direction & MOV_DIR_TOP ? -this->speed
        : direction & MOV_DIR_BOTTOM ? this->speed : 0.f;
    
    if (*dx != 0.f || *dy != 0.f) {
        this->clampMovement(parent, parent_container, dx, dy);
        if (fabsf(*dx) > MOVEMENT_DEADZONE) parent->moveX(*dx);
        if (fabsf(*dy) > MOVEMENT_DEADZONE) parent->moveY(*dy);
    }
}

void Movement::clampMovement(entities::Entity *parent, entities::Zone *parent_container, float *dx, float *dy) {
    Collider *collider = static_cast<Collider*>(parent->getComponent(COMP_COLLIDER));
    if (!collider)
        return;

    systems::ZoneSystem &zone_system = systems::ZoneSystem::getInstance();
    for (entities::Entity *entity : zone_system.getComplexEntities()) {
        collider->clampMovement(parent, parent_container, entity, zone_system.getActualZone(), dx, dy);
        if (fabsf(*dx) <= MOVEMENT_DEADZONE && fabsf(*dy) <= MOVEMENT_DEADZONE)
            break;
    }
}