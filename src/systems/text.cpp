#include "systems/text.hpp"
#include "utils/constants.hpp"

using namespace systems;

TextSystem &TextSystem::getInstance() {
    static TextSystem instance;
    return instance;
}

TextSystem::TextSystem() {
    this->font = C2D_FontLoad(FONT_PATH);
    if (!this->font)
        svcBreak(USERBREAK_PANIC);
    this->buffer = C2D_TextBufNew(UINT8_MAX);
}

TextSystem::~TextSystem() {
    C2D_TextBufDelete(this->buffer);
    C2D_FontFree(this->font);
}

C2D_Text TextSystem::generateText(const char *text) {
    C2D_TextBufClear(this->buffer);
    C2D_Text text_glyphs;
    C2D_TextFontParse(&text_glyphs, this->font, this->buffer, text);
    if (text_glyphs.end)
        C2D_TextOptimize(&text_glyphs);

    return text_glyphs;
}

void TextSystem::writeText(C2D_Text text, float x, float y, float scale, u32 flags) {
    if (text.end) {
        C2D_DrawText(&text, flags, x, y, Z_INDEX_UI, scale, scale);
    }
}

void TextSystem::writeTextWithColor(C2D_Text text, float x, float y, float scale, u32 color, u32 flags) {
    if (text.end) {
        C2D_DrawText(&text, C2D_WithColor | flags, x, y, Z_INDEX_UI, scale, scale, color);
    }
}