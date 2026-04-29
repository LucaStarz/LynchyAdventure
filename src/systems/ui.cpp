#include "systems/game.hpp"
using namespace systems;

UISystem &UISystem::getInstance() {
    static UISystem instance;
    return instance;
}

UISystem::UISystem() {

}

UISystem::~UISystem() {
    // Do nothing
}

void UISystem::renderTopScreenUI() {

}

void UISystem::renderBottomScreenUI() {
    this->renderLife(GameSystem::getInstance().getPlayer());
}

void UISystem::renderLife(entities::Player *player) {
    components::LifeManager *life_manager = static_cast<components::LifeManager*>(player->getComponent(COMP_LIFE));
    GraphicsSystem &gfx_system = GraphicsSystem::getInstance();

    u8 actual_life = life_manager->getActualLife();
    float x = 4.f, y = 4.f;
    for (u8 i = 0; i < life_manager->getMaxLife() / 3; i++) {
        u16 sprite_index = 0;
        if (actual_life >= 3) {
            sprite_index = 3;
            actual_life -= 3;
        } else {
            sprite_index = actual_life;
            actual_life = 0;
        }

        C2D_DrawImageAt(
            gfx_system.getSprite(18, sprite_index),
            x, y,
            Z_INDEX_BACKGROUND, nullptr,
            0.75f, 0.75f
        );

        x += 13.f;
        if (x >= 130.f) {
            x = 4.f;
            y += 13.f;
        }
    }
}