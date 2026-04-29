#include "systems/game.hpp"
using namespace components;

SquaredDetector::SquaredDetector(float size, float parent_size) {
    this->size = size;
    this->parent_size = parent_size / 2.f;
}

SquaredDetector::~SquaredDetector() {
    // Do nothing
}

void SquaredDetector::render(entities::Entity *parent, float depth, entities::Zone *container) {
#ifdef LYNCHY_DEBUG
    C2D_DrawRectSolid(
        parent->getX() + this->parent_size - this->size + container->getX(), 
        parent->getY() + this->parent_size - this->size + container->getY(),
        Z_INDEX_UI,
        this->size * 2.f, this->size * 2.f,
        DEBUG_SQR_DET_COLOR()
    );
#endif
}

void SquaredDetector::getMovement(entities::Entity *parent, entities::Zone *parent_container, entities::Entity *other, entities::Zone *other_container, float *dx, float *dy) {
    float dist_x = parent_container->getX() + parent->getX() + this->parent_size - other->getX() - other_container->getX();
    float dist_y = parent_container->getY() + parent->getY() + this->parent_size - other->getY() - other_container->getY();

    float dist = dist_x * dist_x + dist_y * dist_y;
    if (dist < this->size * this->size) {
        float length = sqrtf(dist);
        *dx = -(dist_x / length);
        *dy = -(dist_y / length);
    }
}