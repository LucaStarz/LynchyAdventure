#pragma once

#include "components/movement.hpp"

namespace components {
    class SquaredDetector : public Component {
    public:
        SquaredDetector(float size, float parent_size);
        ~SquaredDetector();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;

        void getMovement(entities::Entity *parent, entities::Zone *parent_container, entities::Entity *other, entities::Zone *other_container, float *dx, float *dy);
    private:
        float size, parent_size;
    };
}