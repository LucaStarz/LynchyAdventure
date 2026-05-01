#pragma once

#include "entities/player.hpp"

namespace systems {
    class UISystem final {
    public:
        static UISystem &getInstance();

        UISystem(const UISystem&) = delete;
        UISystem &operator=(const UISystem&) = delete;

        void renderTopScreenUI();
        void renderBottomScreenUI();
    private:
        UISystem();
        ~UISystem();

        void renderLife(entities::Player *player);
    };
}