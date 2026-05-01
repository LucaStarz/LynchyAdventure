#pragma once

#include "components/component.hpp"
#include <3ds.h>

namespace components {
    class SquaredDetector : public Component {
    public:
        SquaredDetector(float size);
        ~SquaredDetector();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;

        u8 getDirectionTo(entities::Entity *parent, entities::Zone *parent_container, entities::Entity *other, entities::Zone *other_container);
    private:
        float size;
    };
}