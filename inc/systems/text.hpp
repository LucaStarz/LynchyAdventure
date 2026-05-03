#pragma once

#include <3ds.h>
#include <citro2d.h>

namespace systems {
    class TextSystem final {
    public:
        static TextSystem &getInstance();

        TextSystem(const TextSystem&) = delete;
        TextSystem &operator=(const TextSystem&) = delete;

        C2D_Text generateText(const char *text);
        void writeText(C2D_Text text, float x, float y, float scale, u32 flags);
        void writeTextWithColor(C2D_Text text, float x, float y, float scale, u32 color, u32 flags);
    private:
        C2D_Font font;
        C2D_TextBuf buffer;

        TextSystem();
        ~TextSystem();
    };
}