#pragma once

#include "components/component.hpp"
#include <3ds.h>

namespace components {
    class Hurtbox : public Component {
    public:
        Hurtbox(u8 visible, float x, float y, float width, float height);
        ~Hurtbox();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;
    
        float getX() const;
        float getY() const;
        float getWidth() const;
        float getHeight() const;
        u8 getVisible() const;
    private:
        float x, y, width, height;
        u8 visible;
    };
}