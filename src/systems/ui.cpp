#include "systems/ui.hpp"
#include "systems/gfx.hpp"
#include "systems/game.hpp"
#include "systems/text.hpp"
#include "utils/constants.hpp"

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
    entities::Player *player = GameSystem::getInstance().getPlayer();

    this->renderLife(player);
    this->renderCoins(player);
}

void UISystem::renderLife(entities::Player *player) {
    components::LifeManager *life_manager = player->getLifeManager();
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
            gfx_system.getSprite(utils::SPRT_LIFE_RECEPTACLE, sprite_index),
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

void UISystem::renderCoins(entities::Player *player) {
    char coins_number[7];
    sprintf(coins_number, "%lu", player->getCoins());

    TextSystem &text_system = TextSystem::getInstance();
    C2D_Text coins_text = text_system.generateText(coins_number);
    TextSystem::getInstance().writeTextWithColor(coins_text, 304.f, 2.25f, 0.5f, C2D_Color32(200, 200, 200, 255), C2D_AlignRight);

    C2D_DrawImageAt(
        GraphicsSystem::getInstance().getSprite(utils::SPRT_COIN, 0),
        306.f, 5.f,
        Z_INDEX_BACKGROUND, nullptr,
        1.f, 1.f
    );
}