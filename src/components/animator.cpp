#include "components/animator.hpp"
#include "components/movement.hpp"
#include "entities/zone.hpp"
#include "utils/constants.hpp"
#include <citro2d.h>
#include "systems/gfx.hpp"

#define LEFT_DIR    0
#define RIGHT_DIR   1
#define TOP_DIR     2
#define BOTTOM_DIR  3

using namespace components;

Animator::Animator() {
    this->current_animation = 0;
    this->current_index = 0;
    this->current_time = 0;
    this->direction = utils::FIX_DIR_BOTTOM;
}

Animator::~Animator() {

}

void Animator::update(entities::Entity *parent, entities::Zone *container) {
    u8 animation_index = this->oriented_animations[this->current_animation].ids[this->direction];
    Animation animation = this->animations[animation_index];

    this->current_time += 1;
    if (this->current_time >= animation.duration) {
        this->current_index += 1;
        if (this->current_index > animation.last_index)
            this->current_index = animation.first_index;
        
        this->current_time = 0;
    }

    Movement *movement = parent->getMovement();
    if (!movement)
        return;
    
    float dx = movement->getDx();
    float dy = movement->getDy();
    if (dx > MOVEMENT_DEADZONE) {
        this->direction = utils::FIX_DIR_RIGHT;
    } else if (dx < -MOVEMENT_DEADZONE) {
        this->direction = utils::FIX_DIR_LEFT;
    } else if (dy > MOVEMENT_DEADZONE) {
        this->direction = utils::FIX_DIR_BOTTOM;
    } else if (dy < -MOVEMENT_DEADZONE) {
        this->direction = utils::FIX_DIR_TOP;
    }
}

void Animator::render(entities::Entity *parent, float depth, entities::Zone *container) {
    u8 animation_index = this->oriented_animations[this->current_animation].ids[this->direction];
    Animation animation = this->animations[animation_index];

    C2D_Image sprite = systems::GraphicsSystem::getInstance().getSprite(animation.spritesheet, this->current_index);
    if (!sprite.subtex)
        return;

    C2D_DrawImageAt(
        sprite,
        parent->getX() + container->getX(), parent->getY() + container->getY(),
        depth, nullptr,
        parent->getWidth() / (float)sprite.subtex->width, parent->getHeight() / (float)sprite.subtex->height
    );
}

u8 Animator::addAnimation(utils::SPRITESHEETS_ID spritesheet, u16 first_index, u16 last_index, u8 duration) {
    Animation anim;
    anim.spritesheet = spritesheet;
    anim.first_index = first_index;
    anim.last_index = last_index;
    anim.duration = duration;

    this->animations.push_back(anim);
    return this->animations.size() - 1;
}

void Animator::addOrientedAnimation(u8 left, u8 right, u8 top, u8 bottom) {
    OrientedAnimation anim;
    anim.ids[utils::FIX_DIR_LEFT] = left;
    anim.ids[utils::FIX_DIR_RIGHT] = right;
    anim.ids[utils::FIX_DIR_TOP] = top;
    anim.ids[utils::FIX_DIR_BOTTOM] = bottom;
    this->oriented_animations.push_back(anim);
}

void Animator::addNonOrientedAnimation(u8 index) {
    OrientedAnimation anim;
    anim.ids[0] = anim.ids[1] = anim.ids[2] = anim.ids[3] = index;
    this->oriented_animations.push_back(anim);
}

void Animator::addDeadAnimation() {
    this->addNonOrientedAnimation(
        this->addAnimation(utils::SPRT_DEAD, 0, 5, 6)
    );
}

void Animator::setCurrentAnimation(u8 animation) {
    if (animation >= this->oriented_animations.size() || animation == this->current_animation)
        return;
    
    this->current_animation = animation;
    this->current_time = 0;
    
    u8 animation_index = this->oriented_animations[this->current_animation].ids[this->direction];
    this->current_index = this->animations[animation_index].first_index;
}

utils::FIXED_DIRECTION Animator::getDirection() const {
    return this->direction;
}

bool Animator::isAnimationFinished() const {
    u8 animation_index = this->oriented_animations[this->current_animation].ids[this->direction];
    Animation animation = this->animations[animation_index];

    return this->current_index >= animation.last_index && this->current_time >= animation.duration - 1;
}