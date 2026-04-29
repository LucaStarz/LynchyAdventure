#include "systems/game.hpp"
using namespace entities;

Collision::Collision(float x, float y, float width, float height, u8 visible_on)
    : Entity(x, y) {
    this->addComponent(
        new components::Collider(visible_on, COL_LAYER_NONE, 0.f, 0.f, width, height),
        COMP_COLLIDER
    );
}

Collision::~Collision() {
    // Do nothing
}

#ifdef LYNCHY_DEBUG
void Collision::render(float depth, Zone *container) {
    this->getComponent(COMP_COLLIDER)->render(this, depth, container);
}
#endif