#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <unordered_map>
#include <vector>
#include "utils/spritesheets.hpp"

namespace systems {
    typedef struct {
        C2D_SpriteSheet spritesheet;
        std::vector<C2D_Image> sprites;
        u8 loading_count;
    } SpriteSheet;

    class GraphicsSystem final {
    public:
        static GraphicsSystem &getInstance();

        GraphicsSystem(const GraphicsSystem&) = delete;
        GraphicsSystem &operator=(const GraphicsSystem&) = delete;
    
        void loadSpritesheet(utils::SPRITESHEETS_ID id);
        void unloadSpritesheet(utils::SPRITESHEETS_ID id);
        C2D_Image getSprite(utils::SPRITESHEETS_ID spritesheet_id, u16 sprite_index);

        void setBackgroundColor(u32 color);

        void drawTopScreen();
        void drawBottomScreen();
    private:
        std::unordered_map<utils::SPRITESHEETS_ID, SpriteSheet> spritesheets;
        C3D_RenderTarget *top_screen, *bottom_screen;
        u32 background_color;
    
        GraphicsSystem();
        ~GraphicsSystem();

        void loadCommonSpritesheets();
    };
}