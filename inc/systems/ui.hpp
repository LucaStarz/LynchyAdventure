#pragma once

#include "systems/save.hpp"

namespace systems {
    class UISystem {
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