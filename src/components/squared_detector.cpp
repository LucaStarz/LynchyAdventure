#include "components/squared_detector.hpp"
#include "entities/zone.hpp"
#include <citro2d.h>
#include "utils/utilities.hpp"
#include "utils/constants.hpp"
#include "utils/directions.hpp"

using namespace components;

SquaredDetector::SquaredDetector(float size) {
    this->size = size;
}

SquaredDetector::~SquaredDetector() {
    // Do nothing
}

void SquaredDetector::render(entities::Entity *parent, float depth, entities::Zone *container) {
#ifdef LYNCHY_DEBUG
    C2D_DrawRectSolid(
        parent->getX() + parent->getWidth() / 2 + container->getX() - this->size,
        parent->getY() + parent->getHeight() / 2 + container->getY() - this->size,
        Z_INDEX_UI,
        this->size * 2.f, this->size * 2.f,
        DEBUG_SQR_DET_COLOR()
    );
#endif
}

u8 SquaredDetector::getDirectionTo(entities::Entity *parent, entities::Zone *parent_container, entities::Entity *other, entities::Zone *other_container) {
    float dist_x = parent_container->getX() + parent->getX() + parent->getWidth() / 2.f - other->getX() - other_container->getX() - other->getWidth() / 2.f;
    float dist_y = parent_container->getY() + parent->getY() + parent->getHeight() / 2.f - other->getY() - other_container->getY() - other->getHeight() / 2.f;

    float dist = dist_x * dist_x + dist_y * dist_y;
    if (dist < this->size * this->size) {
        u8 direction = utils::MOV_DIR_NONE;
        if (dist_x > MOVEMENT_DEADZONE * 5.f)
            direction |= utils::MOV_DIR_LEFT;
        else if (dist_x < -MOVEMENT_DEADZONE * 5.f)
            direction |= utils::MOV_DIR_RIGHT;
        
        if (dist_y > MOVEMENT_DEADZONE * 5.f)
            direction |= utils::MOV_DIR_TOP;
        else if (dist_y < -MOVEMENT_DEADZONE * 5.f)
            direction |= utils::MOV_DIR_BOTTOM;

        return direction;
    }

    return utils::MOV_DIR_NONE;
}