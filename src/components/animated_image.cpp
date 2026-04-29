#include "systems/game.hpp"
using namespace components;

AnimatedImage::AnimatedImage(u16 spritesheet_id, u16 first_index, u16 last_index, u8 duration, float scale) {
    this->spritesheet_id = spritesheet_id;
    this->current_index = first_index;
    this->first_index = first_index;
    this->last_index = last_index;
    this->scale = scale;

    this->actual_time = 0;
    this->sprite_duration = duration;
}

AnimatedImage::~AnimatedImage() {
    // Do nothing
}

void AnimatedImage::update(entities::Entity *parent, entities::Zone *container) {
    this->actual_time += 1;
    if (this->actual_time >= this->sprite_duration) {
        this->current_index += 1;
        if (this->current_index > this->last_index)
            this->current_index = this->first_index;
        
        this->actual_time = 0;
    }
}

void AnimatedImage::render(entities::Entity *parent, float depth, entities::Zone *container) {
    systems::GraphicsSystem &gfx_system = systems::GraphicsSystem::getInstance();
    C2D_DrawImageAt(
        gfx_system.getSprite(this->spritesheet_id, this->current_index),
        parent->getX() + container->getX(), parent->getY() + container->getY(),
        depth, nullptr,
        this->scale, this->scale
    );
}

void AnimatedImage::animate(float dx, float dy, u16 left_spritesheet_id, u16 first_index, u16 last_index, u16 reset_index) {
    if (dx > MOVEMENT_DEADZONE) {
        this->setSpriteSheet(left_spritesheet_id + 2);
        this->setAnimation(first_index, last_index, reset_index);
    } else if (dx < -MOVEMENT_DEADZONE) {
        this->setSpriteSheet(left_spritesheet_id);
        this->setAnimation(first_index, last_index, reset_index);
    } else if (dy > MOVEMENT_DEADZONE) {
        this->setSpriteSheet(left_spritesheet_id + 3);
        this->setAnimation(first_index, last_index, reset_index);
    } else if (dy < -MOVEMENT_DEADZONE) {
        this->setSpriteSheet(left_spritesheet_id + 1);
        this->setAnimation(first_index, last_index, reset_index);
    } else
        this->setAnimation(0, 0, 0);
}

void AnimatedImage::setSpriteSheet(u16 spritesheet_id) {
    if (this->spritesheet_id != spritesheet_id) {
        this->spritesheet_id = spritesheet_id;
        this->actual_time = 0;
        this->current_index = this->first_index;
    }
}

void AnimatedImage::setAnimation(u16 first_index, u16 last_index, u16 current_index) {
    if (this->first_index != first_index || this->last_index != last_index) {
        this->first_index = first_index;
        this->last_index = last_index;
        this->actual_time = 0;
        this->current_index = current_index;
    }
}

void AnimatedImage::setDuration(u8 duration) {
    this->sprite_duration = duration;
}

u16 AnimatedImage::getSpritesheetId() const {
    return this->spritesheet_id;
}