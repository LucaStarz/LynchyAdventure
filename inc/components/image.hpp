#pragma once

#include "components/component.hpp"
#include <3ds.h>

namespace components {
    class ImageComponent : public Component {
    public:
        ImageComponent(u16 spritesheet_id, u16 sprite_index);
        virtual ~ImageComponent();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;
    
        void setSpritesheetId(u16 spritesheet_id);
        void setSpriteIndex(u16 index);

        u16 getSpritesheetId() const;
    protected:
        u16 spritesheet_id, sprite_index;
    };
}