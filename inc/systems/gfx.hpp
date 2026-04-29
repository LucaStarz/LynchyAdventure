#pragma once

#include "entities/bamboo.hpp"

namespace systems {
    typedef struct {
        C2D_SpriteSheet spritesheet;
        std::vector<C2D_Image> sprites;
        u8 loading_count;
    } SpriteSheet;

    class GraphicsSystem {
    public:
        static GraphicsSystem &getInstance();

        GraphicsSystem(const GraphicsSystem&) = delete;
        GraphicsSystem &operator=(const GraphicsSystem&) = delete;
    
        void loadSpritesheet(u16 id);
        void unloadSpritesheet(u16 id);
        C2D_Image getSprite(u16 spritesheet_id, u16 index);

        void setBackgroundColor(u32 color);

        void drawTopScreen();
        void drawBottomScreen();
    private:
        std::unordered_map<u16, SpriteSheet*> spritesheets;
        C3D_RenderTarget *top_screen, *bottom_screen;
        u32 background_color;
    
        GraphicsSystem();
        ~GraphicsSystem();
    };
}