#pragma once

#include "entities/entity.hpp"

namespace entities {
    class Tile : public Entity {
    public:
        Tile(float x, float y, u16 spritesheet_id, u16 index, float scale);
        ~Tile();

        void render(float depth, Zone *container) override;
    };
}