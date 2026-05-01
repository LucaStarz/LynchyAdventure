#include "entities/tile.hpp"

using namespace entities;

Tile::Tile(float x, float y, float width, float height, u16 spritesheet_id, u16 index)
    : Entity(x, y, width, height) {
    this->image = new components::ImageComponent(spritesheet_id, index);
}

Tile::~Tile() {
    delete this->image;
}

void Tile::render(float depth, Zone *container) {
    this->image->render(this, depth, container);
}