#pragma once

#include "components/hurtbox.hpp"

namespace components {
    class Movement : public Component {
    public:
        Movement(float speed);
        ~Movement();

        void applyMovement(entities::Entity *parent, entities::Zone *parent_container, u8 direction, float *dx, float *dy);
    private:
        float speed;

        void clampMovement(entities::Entity *parent, entities::Zone *parent_container, float *dx, float *dy);
    };
}