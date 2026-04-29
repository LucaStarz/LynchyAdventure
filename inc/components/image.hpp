#pragma once

#include "components/component.hpp"

namespace components {
    class ImageComponent : public Component {
    public:
        ImageComponent(u16 spritesheet_id, u16 index, float scale);
        ~ImageComponent();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;
    
        void setSpritesheetId(u16 spritesheet_id);
        void setSpriteIndex(u16 index);
        void setScale(float scale);
    private:
        u16 spritesheet_id, index;
        float scale;
    };
}