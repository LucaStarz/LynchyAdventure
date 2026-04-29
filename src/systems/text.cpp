#include "systems/game.hpp"
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

void TextSystem::writeText(const char *text, float x, float y, float scale) {
    C2D_TextBufClear(this->buffer);

    C2D_Text text_glyphs;
    C2D_TextFontParse(&text_glyphs, this->font, this->buffer, text);
    if (text_glyphs.end) {
        C2D_TextOptimize(&text_glyphs);
        C2D_DrawText(&text_glyphs, 0, x, y, Z_INDEX_UI, scale, scale);
    }
}

void TextSystem::writeTextWithColor(const char *text, float x, float y, float scale, u32 color) {
    C2D_TextBufClear(this->buffer);

    C2D_Text text_glyphs;
    C2D_TextFontParse(&text_glyphs, this->font, this->buffer, text);
    
    if (text_glyphs.end) {
        C2D_TextOptimize(&text_glyphs);
        C2D_DrawText(&text_glyphs, C2D_WithColor, x, y, Z_INDEX_UI, scale, scale, color);
    }
}