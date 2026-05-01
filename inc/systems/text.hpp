#pragma once

#include <3ds.h>
#include <citro2d.h>

namespace systems {
    class TextSystem final {
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