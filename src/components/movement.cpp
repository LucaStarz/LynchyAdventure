#include "components/movement.hpp"
#include "utils/directions.hpp"
#include "utils/constants.hpp"
#include <cmath>
#include "entities/zone.hpp"
#include <systems/zone_system.hpp>

using namespace components;

Movement::Movement(float speed) {
    this->speed = speed;
    this->dx = 0.f;
    this->dy = 0.f;
}

Movement::~Movement() {
    // Do nothing
}

void Movement::applyMovement(entities::Entity *parent, entities::Zone *parent_container, u8 direction) {
    this->dx = direction & utils::MOV_DIR_LEFT ? -this->speed
        : direction & utils::MOV_DIR_RIGHT ? this->speed : 0.f;
    
    this->dy = direction & utils::MOV_DIR_TOP ? -this->speed
        : direction & utils::MOV_DIR_BOTTOM ? this->speed : 0.f;
    
    if (this->dx != 0.f || this->dy != 0.f) {
        float length = sqrtf(this->dx * this->dx + this->dy * this->dy);
        if (length > 0.f) {
            float nx = this->dx / length;
            float ny = this->dy / length;
            this->dx = nx * this->speed;
            this->dy = ny * this->speed;
        }

        this->clampMovement(parent, parent_container);
        if (fabsf(this->dx) > MOVEMENT_DEADZONE) parent->moveX(this->dx);
        if (fabsf(this->dy) > MOVEMENT_DEADZONE) parent->moveY(this->dy);
    }
}

float Movement::getSpeed() const {
    return this->speed;
}

float Movement::getDx() const {
    return this->dx;
}

float Movement::getDy() const {
    return this->dy;
}

void Movement::clampMovement(entities::Entity *parent, entities::Zone *parent_container) {
    systems::ZoneSystem &zone_system = systems::ZoneSystem::getInstance();
    if (!this->clampMovementForZone(parent, parent_container, zone_system.getActualZone())) return;
    if (!this->clampMovementForZone(parent, parent_container, zone_system.getLeftZone())) return;
    if (!this->clampMovementForZone(parent, parent_container, zone_system.getTopZone())) return;
    if (!this->clampMovementForZone(parent, parent_container, zone_system.getRightZone())) return;
    if (!this->clampMovementForZone(parent, parent_container, zone_system.getBottomZone())) return;
}

bool Movement::clampMovementForZone(entities::Entity *parent, entities::Zone *parent_container, entities::Zone *zone) {
    for (entities::Entity *entity : zone->getComplexEntities()) {
        parent->getCollider()->clampMovement(parent, parent_container, entity, zone, &this->dx, &this->dy);
        if (fabsf(this->dx) <= MOVEMENT_DEADZONE && fabsf(this->dy) <= MOVEMENT_DEADZONE)
            return false;
    }

    return true;
}