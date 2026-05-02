#pragma once

#include "components/image.hpp"

namespace components {
    class AnimatedImage : public ImageComponent {
    public:
        AnimatedImage(utils::SPRITESHEETS_ID spritesheet_id, u16 first_index, u16 last_index, u8 duration);
        ~AnimatedImage();

        void update(entities::Entity *parent, entities::Zone *container) override;

        void setAnimation(u16 first_index, u16 last_index, u16 current_index);
        void setDuration(u8 duration);
    private:
        u16 first_index, last_index;
        u8 sprite_duration, actual_time;
    };
}