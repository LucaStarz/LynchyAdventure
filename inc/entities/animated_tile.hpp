#pragma once

#include "entities/entity.hpp"
#include "components/animated_image.hpp"

namespace entities {
    class AnimatedTile : public Entity {
    public:
        AnimatedTile(float x, float y, float width, float height, utils::SPRITESHEETS_ID spritesheet_id, u16 first_index, u16 last_index, u8 duration);
        ~AnimatedTile();

        bool update(Zone *container) override;
        void render(float depth, Zone *container) override;
    
    private:
        components::AnimatedImage *animated_image;
    };
}