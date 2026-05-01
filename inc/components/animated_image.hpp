#pragma once

#include "components/image.hpp"

namespace components {
    class AnimatedImage : public ImageComponent {
    public:
        AnimatedImage(u16 spritesheet_id, u16 first_index, u16 last_index, u8 duration);
        ~AnimatedImage();

        void update(entities::Entity *parent, entities::Zone *container) override;

        void animateOriented(float dx, float dy, u16 left_spritesheet_id, u16 first_index, u16 last_index, u16 reset_index);

        void setSpriteSheet(u16 spritesheet_id);
        void setAnimation(u16 first_index, u16 last_index, u16 current_index);
        void setDuration(u8 duration);

        u16 getSpritesheetId() const;
    private:
        u16 first_index, last_index;
        u8 sprite_duration, actual_time;
    };
}