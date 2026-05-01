#include "entities/collision.hpp"
#include "utils/collisions.hpp"

using namespace entities;

Collision::Collision(float x, float y, float width, float height, u8 visible_on)
    : Entity(x, y, width, height) {
    this->collider = new components::Collider(visible_on, utils::COL_LAYER_NONE, 0.f, 0.f, width, height);
}

Collision::~Collision() {
    delete this->collider;
}

#ifdef LYNCHY_DEBUG
void Collision::render(float depth, Zone *container) {
    this->collider->render(this, depth, container);
}
#endif

components::Collider *Collision::getCollider() const {
    return this->collider;
}