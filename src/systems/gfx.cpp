#include "systems/gfx.hpp"
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

    for (u16 i = 7; i < 11; i++)
        this->loadSpritesheet(i);   // Player spritesheets
    this->loadSpritesheet(18);      // Life receptacle spritesheet
}

GraphicsSystem::~GraphicsSystem() {
    for (auto &spritesheet : this->spritesheets) {
        C2D_SpriteSheetFree(spritesheet.second->spritesheet);
        delete spritesheet.second;
    }

    C3D_RenderTargetDelete(this->top_screen);
    
#ifndef LYNCHY_DEBUG
    C3D_RenderTargetDelete(this->bottom_screen);
#endif

    C2D_Fini();
    C3D_Fini();
    gfxExit();
}

void GraphicsSystem::loadSpritesheet(u16 id) {
    auto spritesheet = this->spritesheets.find(id);
    if (spritesheet != this->spritesheets.end()) {
        spritesheet->second->loading_count += 1;
        return;
    }
    
    SpriteSheet *new_spritesheet = new SpriteSheet;
    char filename[48];
    sprintf(filename, GFX_PATH, id);
    new_spritesheet->spritesheet = C2D_SpriteSheetLoad(filename);
    new_spritesheet->loading_count = 1;
    if (!new_spritesheet->spritesheet) {
        PRINT("Failed to load spritesheet %u\n", id);
        return;
    }
    
    u16 sprites_count = C2D_SpriteSheetCount(new_spritesheet->spritesheet);
    new_spritesheet->sprites.reserve(sprites_count);
    for (u16 i = 0; i < sprites_count; i++)
        new_spritesheet->sprites[i] = std::move(C2D_SpriteSheetGetImage(new_spritesheet->spritesheet, i));
    
    PRINT("Spritesheet %u was loaded\n", id);
    this->spritesheets[id] = new_spritesheet;
}

void GraphicsSystem::unloadSpritesheet(u16 id) {
    auto spritesheet = this->spritesheets.find(id);
    if (spritesheet == this->spritesheets.end())
        return;
    
    spritesheet->second->loading_count -= 1;
    if (!spritesheet->second->loading_count) {
        PRINT("Spritesheet %u was unloaded\n", id);
        this->spritesheets.erase(spritesheet);
    }
}

C2D_Image GraphicsSystem::getSprite(u16 spritesheet_id, u16 index) {
    auto spritesheet = this->spritesheets.find(spritesheet_id);
    if (spritesheet == this->spritesheets.end())
        return C2D_Image{ nullptr, nullptr };

    return spritesheet->second->sprites[index];
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