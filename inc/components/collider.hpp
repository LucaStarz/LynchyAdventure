#pragma once

#include "components/animated_image.hpp"

namespace components {
    class Collider : public Component {
    public:
        Collider(u8 visible, u8 scan, float x, float y, float width, float height);
        ~Collider();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;

        void clampMovement(entities::Entity *parent, entities::Zone *parent_container, entities::Entity *other, entities::Zone *other_container, float *dx, float *dy);
        bool checkCollision(entities::Entity *parent, entities::Zone *parent_container, entities::Entity *other, entities::Zone *other_container);

        float getX() const;
        float getY() const;
        float getWidth() const;
        float getHeight() const;
    private:
        float x, y, width, height;
        u8 visible, scan;
    };
}