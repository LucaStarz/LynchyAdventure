#include "systems/gfx.hpp"
#include "utils/constants.hpp"
#include "utils/utilities.hpp"
#include "utils/spritesheets.hpp"

using namespace systems;

GraphicsSystem &GraphicsSystem::getInstance() {
    static GraphicsSystem instance;
    return instance;
}

GraphicsSystem::GraphicsSystem() {
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    this->top_screen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    this->background_color = C2D_Color32(41, 41, 41, 255);

#ifdef LYNCHY_DEBUG
    consoleInit(GFX_BOTTOM, nullptr);
#else
    this->bottom_screen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
#endif

    this->loadCommonSpritesheets();
}

GraphicsSystem::~GraphicsSystem() {
    for (auto &spritesheet : this->spritesheets) {
        C2D_SpriteSheetFree(spritesheet.second.spritesheet);
    }

    C3D_RenderTargetDelete(this->top_screen);
    
#ifndef LYNCHY_DEBUG
    C3D_RenderTargetDelete(this->bottom_screen);
#endif

    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

void GraphicsSystem::loadCommonSpritesheets() {
    for (u16 i = utils::SPRT_PLAYER_LEFT; i <= utils::SPRT_PLAYER_BOTTOM; i++)
        this->loadSpritesheet((utils::SPRITESHEETS_ID)i);

    this->loadSpritesheet(utils::SPRT_LIFE_RECEPTACLE);
    this->loadSpritesheet(utils::SPRT_DEAD);
    this->loadSpritesheet(utils::SPRT_COIN);
    this->loadSpritesheet(utils::SPRT_HEART);
}

void GraphicsSystem::loadSpritesheet(utils::SPRITESHEETS_ID id) {
    auto spritesheet = this->spritesheets.find(id);
    if (spritesheet != this->spritesheets.end()) {
        spritesheet->second.loading_count += 1;
        return;
    }
    
    SpriteSheet new_spritesheet;
    char filename[48];
    sprintf(filename, GFX_PATH, id);
    new_spritesheet.spritesheet = C2D_SpriteSheetLoad(filename);
    new_spritesheet.loading_count = 1;
    if (!new_spritesheet.spritesheet) {
        PRINT("Failed to load spritesheet %u\n", id);
        return;
    }
    
    u16 sprites_count = C2D_SpriteSheetCount(new_spritesheet.spritesheet);
    new_spritesheet.sprites.reserve(sprites_count);
    for (u16 i = 0; i < sprites_count; i++)
        new_spritesheet.sprites[i] = std::move(C2D_SpriteSheetGetImage(new_spritesheet.spritesheet, i));
    
    PRINT("Spritesheet %u was loaded\n", id);
    this->spritesheets[id] = std::move(new_spritesheet);
}

void GraphicsSystem::unloadSpritesheet(utils::SPRITESHEETS_ID id) {
    auto spritesheet = this->spritesheets.find(id);
    if (spritesheet == this->spritesheets.end())
        return;
    
    spritesheet->second.loading_count -= 1;
    if (!spritesheet->second.loading_count) {
        PRINT("Spritesheet %u was unloaded\n", id);
        this->spritesheets.erase(spritesheet);
    }
}

C2D_Image GraphicsSystem::getSprite(utils::SPRITESHEETS_ID spritesheet_id, u16 sprite_index) {
    auto spritesheet = this->spritesheets.find(spritesheet_id);
    if (spritesheet == this->spritesheets.end() || sprite_index >= spritesheet->second.sprites.capacity())
        return { nullptr, nullptr };
    
    return spritesheet->second.sprites[sprite_index];
}

void GraphicsSystem::setBackgroundColor(u32 color) {
    this->background_color = color;
}

void GraphicsSystem::drawTopScreen() {
    C2D_TargetClear(this->top_screen, this->background_color);
    C2D_SceneBegin(this->top_screen);
}

void GraphicsSystem::drawBottomScreen() {
    C2D_TargetClear(this->bottom_screen, this->background_color);
    C2D_SceneBegin(this->bottom_screen);
}