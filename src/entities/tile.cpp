#include "systems/game.hpp"
using namespace entities;

Tile::Tile(float x, float y, u16 spritesheet_id, u16 index, float scale)
    : Entity(x, y) {
    this->addComponent(
        new components::ImageComponent(spritesheet_id, index, scale),
        COMP_IMAGE
    );
}

Tile::~Tile() {
    // Do nothing
}

void Tile::render(float depth, Zone *container) {
    this->getComponent(COMP_IMAGE)->render(this, depth, container);
}