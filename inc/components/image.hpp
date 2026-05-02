#pragma once

#include "components/component.hpp"
#include <3ds.h>
#include "utils/spritesheets.hpp"

namespace components {
    class ImageComponent : public Component {
    public:
        ImageComponent(utils::SPRITESHEETS_ID spritesheet_id, u16 sprite_index);
        virtual ~ImageComponent();

        void render(entities::Entity *parent, float depth, entities::Zone *container) override;
    
        void setSpritesheetId(utils::SPRITESHEETS_ID spritesheet_id);
        void setSpriteIndex(u16 index);

        utils::SPRITESHEETS_ID getSpritesheetId() const;
    protected:
        utils::SPRITESHEETS_ID spritesheet_id;
        u16 sprite_index;
    };
}