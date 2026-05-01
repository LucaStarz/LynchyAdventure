#pragma once

#include "entities/entity.hpp"

namespace entities {
    class Collision : public Entity {
    public:
        Collision(float x, float y, float width, float height, u8 visible_on);
        ~Collision();

    #ifdef LYNCHY_DEBUG
        void render(float depth, Zone *container) override;
    #endif
        
        components::Collider *getCollider() const override;
    private:
        components::Collider *collider;
    };
}