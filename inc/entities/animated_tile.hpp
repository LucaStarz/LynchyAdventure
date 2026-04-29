#pragma once

#include "entities/tile.hpp"

namespace entities {
    class AnimatedTile : public Entity {
    public:
        AnimatedTile(float x, float y, u16 spritesheet_id, u16 first_index, u16 last_index, u8 duration, float scale);
        ~AnimatedTile();

        void update(Zone *container) override;
        void render(float depth, Zone *container) override;
    };
}