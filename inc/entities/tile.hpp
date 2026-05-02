#pragma once

#include "entities/entity.hpp"
#include "components/image.hpp"
#include "utils/spritesheets.hpp"

namespace entities {
    class Tile : public Entity {
    public:
        Tile(float x, float y, float width, float height, utils::SPRITESHEETS_ID spritesheet_id, u16 index);
        ~Tile();

        void render(float depth, Zone *container) override;
    private:
        components::ImageComponent *image;
    };
}