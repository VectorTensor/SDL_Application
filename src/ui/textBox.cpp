

#include "textBox.h"

bool TextBox::init(SDL_Renderer *renderer, const std::string &bodyFontPath, const std::string &nameFontPath,
                   float bodySize, float nameSize) {
    bodyFont = TTF_OpenFont(bodyFontPath.c_str(), bodySize);
    nameFont = TTF_OpenFont(nameFontPath.c_str(), nameSize);
    return bodyFont && nameFont;
}
void TextBox::setLine(const DialogueLine &line) {
    freeTextures();

    fullText = line.text;
    speaker = line.speaker;
    isNarrator = line.speaker.empty();

    visibleText.clear();
    charIndex = 0;
    charTimer = 0.f;
    typingDone = false;
    textDirty = true;
    nameDirty = true;
    visible = true;
}
void TextBox::update(float deltaMs) {
    if (!visible)
        return;

    if (!typingDone) {
        charTimer += deltaMs;
        while (charTimer >= charInterval && charIndex < fullText.size()) {
            unsigned char c = static_cast<unsigned char>(fullText[charIndex]);

            size_t step = 1;

            if (c >= 0xF0)
                step = 4;
            else if (c >= 0xE0)
                step = 3;
            else if (c >= 0xC0)
                step = 2;

            charIndex = std::min(charIndex + step, fullText.size());
            visibleText = fullText.substr(0, charIndex);

            textDirty = true;

            charTimer -= charInterval;
        }

        if (charIndex >= fullText.size()) {
            visibleText = fullText;
            typingDone = true;
            textDirty = true;
        }
    }

    if (typingDone) {
        cursorTimer += deltaMs;
        if (cursorTimer >= 530.f) {
            cursorVisible = !cursorVisible;
            cursorTimer = 0.f;
        } else {
            cursorVisible = true;
            cursorTimer = 0.f;
        }
    }
}

void TextBox::draw(SDL_Renderer *renderer) {
    if (!visible)
        return;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (!isNarrator) {
        drawRoundedRect(renderer, nameRect, 4.f, COL_NAME_BG);

        SDL_FRect nameBorder = {nameRect.x - 1, nameRect.y - 1, nameRect.w + 2, nameRect.h + 2};

        SDL_SetRenderDrawColor(renderer, COL_NAME_BORDER.r, COL_NAME_BORDER.g, COL_NAME_BORDER.b, COL_NAME_BORDER.a);
        SDL_RenderRect(renderer, &nameBorder);
        if (nameDirty)
            rebuildNameTexture(renderer);

        if (nameTex) {
            int tw, th;
            SDL_GetTextureSize(nameTex, (float *) &tw, (float *) &th);
            SDL_FRect dst = {nameRect.x + 10.f, nameRect.y + (nameRect.h - (float) th) * 0.5f, (float) tw, (float) th};

            SDL_RenderTexture(renderer, nameTex, nullptr, &dst);
        }
    }

    drawRoundedRect(renderer, panelRect, 6.f, COL_PANEL);
    SDL_FRect border = {panelRect.x - 1, panelRect.y - 1, panelRect.w + 2, panelRect.h + 2};

    SDL_SetRenderDrawColor(renderer, COL_PANEL_BORDER.r, COL_PANEL_BORDER.g, COL_PANEL_BORDER.b, COL_PANEL_BORDER.a);

    SDL_RenderRect(renderer, &border);

    if (textDirty)
        rebuildTextTexture(renderer);

    if (textTex) {
        int tw, th;
        SDL_GetTextureSize(textTex, (float *) &tw, (float *) &th);
        SDL_FRect dst = {textRect.x, textRect.y, (float) tw, (float) th};
        SDL_RenderTexture(renderer, textTex, nullptr, &dst);


        if (cursorVisible) {
            float cx = textRect.x + static_cast<float>(tw) + 10.f;
            float cy = textRect.y + static_cast<float>(th) - 10.f;

            SDL_SetRenderDrawColor(renderer, COL_CURSOR.r, COL_CURSOR.g, COL_CURSOR.b, 200);

            SDL_RenderLine(renderer, cx, cy, cx + 7.f, cy + 7.f);
            SDL_RenderLine(renderer, cx + 7.f, cy + 7.f, cx + 14.f, cy);
        }
    }
}

void TextBox::skipToEnd() {
    visibleText = fullText;
    charIndex = fullText.size();
    typingDone = true;
    textDirty = true;
}
bool TextBox::isTypingDone() const {
    return typingDone;
}
void TextBox::setLayout(float x, float y, float w, float h) {
    panelRect = {x, y, w, h};
    nameRect = {x + padding, y - nameTabH, 160.8f, nameTabH};
    textRect = {x + padding, y + padding, w - padding * 2.0f, h - padding * 2.0f};
}

void TextBox::hide() {
    visible = false;
}

void TextBox::show() {
    visible = true;
}
