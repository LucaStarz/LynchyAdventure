#pragma once

#include "components/hitbox.hpp"

namespace components {
    class Hurtbox : public Component {
    public:
        Hurtbox(u8 visible, float x, float y, float width, float height);
        ~Hurtbox();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;
    private:
        float x, y, width, height;
        u8 visible;
    };
}