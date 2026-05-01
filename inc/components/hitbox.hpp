#pragma once

#include "components/component.hpp"
#include <3ds.h>

namespace components {
    class Hitbox : public Component {
    public:
        Hitbox(u8 scan, u8 damage, float x, float y, float width, float height);
        ~Hitbox();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;

        void checkHurtbox(entities::Entity *parent, entities::Zone *container, entities::Entity *other, entities::Zone *other_container);

        void setDamage(u8 damage);
        void setWidth(float width);
        void setHeight(float height);
    private:
        float x, y, width, height;
        u8 scan, damage;
    };
}