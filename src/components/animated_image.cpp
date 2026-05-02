#include "components/animated_image.hpp"
#include "utils/constants.hpp"

using namespace components;

AnimatedImage::AnimatedImage(utils::SPRITESHEETS_ID spritesheet_id, u16 first_index, u16 last_index, u8 duration)
    : ImageComponent(spritesheet_id, first_index) {
    this->first_index = first_index;
    this->last_index = last_index;

    this->actual_time = 0;
    this->sprite_duration = duration;
}

AnimatedImage::~AnimatedImage() {
    // Do nothing
}

void AnimatedImage::update(entities::Entity *parent, entities::Zone *container) {
    this->actual_time += 1;
    if (this->actual_time >= this->sprite_duration) {
        this->sprite_index += 1;
        if (this->sprite_index > this->last_index)
            this->sprite_index = this->first_index;
        
        this->actual_time = 0;
    }
}

void AnimatedImage::setAnimation(u16 first_index, u16 last_index, u16 current_index) {
    if (this->first_index != first_index || this->last_index != last_index) {
        this->first_index = first_index;
        this->last_index = last_index;
        this->actual_time = 0;
        this->sprite_index = current_index;
    }
}

void AnimatedImage::setDuration(u8 duration) {
    this->sprite_duration = duration;
}