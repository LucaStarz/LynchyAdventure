#pragma once

#include "components/component.hpp"
#include <3ds.h>
#include <vector>
#include "utils/directions.hpp"

namespace components {
    typedef struct {
        u16 spritesheet, first_index, last_index;
        u8 duration;
    } Animation;

    typedef struct {
        u8 ids[4];
    } OrientedAnimation;

    class Animator : public Component {
    public:
        Animator();
        ~Animator();

        void update(entities::Entity *parent, entities::Zone *container) override;
        void render(entities::Entity *parent, float depth, entities::Zone *container) override;
    
        u8 addAnimation(u16 spritesheet, u16 first_index, u16 last_index, u8 duration);
        void addOrientedAnimation(u8 left, u8 right, u8 top, u8 bottom);
        void addNonOrientedAnimation(u8 index);

        void setCurrentAnimation(u8 animation);

        utils::FIXED_DIRECTION getDirection() const;
    private:
        std::vector<Animation> animations;
        std::vector<OrientedAnimation> oriented_animations;

        u16 current_index;
        u8 current_time, current_animation;
        utils::FIXED_DIRECTION direction;
    };
}