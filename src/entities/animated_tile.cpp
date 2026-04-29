#include "systems/game.hpp"
using namespace entities;

AnimatedTile::AnimatedTile(float x, float y, u16 spritesheet_id, u16 first_index, u16 last_index, u8 duration, float scale) 
    : Entity(x, y) {
    this->addComponent(
        new components::AnimatedImage(spritesheet_id, first_index, last_index, duration, scale),
        COMP_IMAGE
    );
}

AnimatedTile::~AnimatedTile() {
    // Do nothing
}

void AnimatedTile::update(Zone *container) {
    this->getComponent(COMP_IMAGE)->update(this, container);
}

void AnimatedTile::render(float depth, Zone *container) {
    this->getComponent(COMP_IMAGE)->render(this, depth, container);
}