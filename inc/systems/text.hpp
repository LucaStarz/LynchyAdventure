#pragma once

#include "systems/zone_system.hpp"

namespace systems {
    class TextSystem {
    public:
        static TextSystem &getInstance();

        TextSystem(const TextSystem&) = delete;
        TextSystem &operator=(const TextSystem&) = delete;

        void writeText(const char *text, float x, float y, float scale);
        void writeTextWithColor(const char *text, float x, float y, float scale, u32 color);
    private:
        C2D_Font font;
        C2D_TextBuf buffer;

        TextSystem();
        ~TextSystem();
    };
}