#pragma once

#include "entities/player.hpp"

namespace entities {
    class Collision : public Entity {
    public:
        Collision(float x, float y, float width, float height, u8 visible_on);
        ~Collision();

    #ifdef LYNCHY_DEBUG
        void render(float depth, Zone *container) override;
    #endif
    };
}