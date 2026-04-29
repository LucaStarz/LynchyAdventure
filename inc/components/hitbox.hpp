#pragma once

#include "components/life.hpp"

namespace components {
    class Hitbox : public Component {
    public:
        Hitbox(u8 scan, float x, float y, float width, float height);
        ~Hitbox();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;
    private:
        float x, y, width, height;
        u8 scan;
    };
}