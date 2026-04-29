#pragma once

#include "systems/ui.hpp"

namespace systems {
    enum GameState : u8 {
        GS_MAIN_MENU = 0,
        GS_IN_GAME,
        GS_TO_LEFT, GS_TO_RIGHT, GS_TO_TOP, GS_TO_BOTTOM,
        GS_PAUSE_MENU, GS_GAME_OVER
    };

    class GameSystem {
    public:
        static GameSystem &getInstance();

        GameSystem(const GameSystem &) = delete;
        GameSystem &operator=(const GameSystem &) = delete;

        void init();
        void update();
        void render();

        void changeState(GameState direction_state);

        entities::Player *getPlayer() const;
    private:
        entities::Player *player;
        GameState state;

        GameSystem();
        ~GameSystem();
    };
}