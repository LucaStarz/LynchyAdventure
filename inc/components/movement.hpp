#pragma once

#include "components/component.hpp"
#include <3ds.h>

namespace components {
    class Movement : public Component {
    public:
        Movement(float speed);
        ~Movement();

        void applyMovement(entities::Entity *parent, entities::Zone *parent_container, u8 direction);
    
        float getSpeed() const;
        float getDx() const;
        float getDy() const;
    private:
        float speed, dx, dy;

        void clampMovement(entities::Entity *parent, entities::Zone *parent_container);
        bool clampMovementForZone(entities::Entity *parent, entities::Zone *parent_container, entities::Zone *zone);
    };
}