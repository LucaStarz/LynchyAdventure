#pragma once

#include "components/component.hpp"
#include <3ds.h>

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

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);

        u8 getVisibleOn() const;
    private:
        float x, y, width, height;
        u8 visible, scan;
    };
}