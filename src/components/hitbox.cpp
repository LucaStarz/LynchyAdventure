#include "systems/game.hpp"
using namespace components;

Hitbox::Hitbox(u8 scan, float x, float y, float width, float height) {
    this->scan = scan;
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