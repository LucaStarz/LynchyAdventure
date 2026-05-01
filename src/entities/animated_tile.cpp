#include "entities/animated_tile.hpp"

using namespace entities;

AnimatedTile::AnimatedTile(float x, float y, float width, float height, u16 spritesheet_id, u16 first_index, u16 last_index, u8 duration) 
    : Entity(x, y, width, height) {
    this->animated_image = new components::AnimatedImage(spritesheet_id, first_index, last_index, duration);
}

AnimatedTile::~AnimatedTile() {
    delete this->animated_image;
}

void AnimatedTile::update(Zone *container) {
    this->animated_image->update(this, container);
}

void AnimatedTile::render(float depth, Zone *container) {
    this->animated_image->render(this, depth, container);
}