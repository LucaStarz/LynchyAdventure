#include "systems/game.hpp"
using namespace components;

Hurtbox::Hurtbox(u8 visible, float x, float y, float width, float height) {
    this->visible = visible;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Hurtbox::~Hurtbox() {
    // Do nothing
}

void Hurtbox::render(entities::Entity *parent, float depth, entities::Zone *container) {
#ifdef LYNCHY_DEBUG
    C2D_DrawRectSolid(
        parent->getX() + this->x + container->getX(), parent->getY() + this->y + container->getY(),
        Z_INDEX_UI,
        this->width, this->height,
        DEBUG_HURTBOX_COLOR()
    );
#endif
}