#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

static constexpr SDL_Color COL_PANEL = {10, 5, 18, 210}; // deep purple, semi-transparent
static constexpr SDL_Color COL_PANEL_BORDER = {60, 30, 90, 180};
static constexpr SDL_Color COL_NAME_BG = {26, 10, 34, 230};
static constexpr SDL_Color COL_NAME_BORDER = {80, 40, 120, 200};
static constexpr SDL_Color COL_BODY_TEXT = {212, 200, 228, 255};
static constexpr SDL_Color COL_NAME_TEXT = {200, 160, 220, 255};
static constexpr SDL_Color COL_NARRATOR = {160, 145, 175, 255}; // italic narrator colour
static constexpr SDL_Color COL_CURSOR = {140, 90, 170, 255};


struct DialogueLine {
    std::string speaker; // empty = narrator
    std::string text;
};

class TextBox {
public:
    bool init(SDL_Renderer *renderer, const std::string &bodyFontPath, const std::string &nameFontPath,
              float bodySize = 20, float nameSize = 15);

    void setLine(const DialogueLine &line);

    void update(float deltaMs);

    void draw(SDL_Renderer *renderer);

    bool isTypingDone() const;

    void skipToEnd();

    void hide();

    void show();

    // Layout — call before first draw
    void setLayout(float x, float y, float w, float h);

private:
    // Fonts
    TTF_Font *bodyFont = nullptr;
    TTF_Font *nameFont = nullptr;

    // Data
    std::string fullText;
    std::string speaker;
    bool isNarrator = false;

    // Typewriter state
    std::string visibleText;
    size_t charIndex = 0;
    float charTimer = 0.f;
    float charInterval = 28.f; // ms per character
    bool typingDone = false;

    // Cached textures
    SDL_Texture *textTex = nullptr;
    SDL_Texture *nameTex = nullptr;
    bool textDirty = true;
    bool nameDirty = true;

    // Cursor blink
    float cursorTimer = 0.f;
    bool cursorVisible = false;

    // Layout
    SDL_FRect panelRect{}; // full textbox panel
    SDL_FRect textRect{}; // area inside panel for body text
    SDL_FRect nameRect{}; // speaker name tab above panel
    float padding = 20.f;
    float nameTabH = 30.f;

    bool visible = true;

    // Helpers
    void rebuildTextTexture(SDL_Renderer *renderer) {
        if (textTex) {
            SDL_DestroyTexture(textTex);
            textTex = nullptr;
        }

        if (visibleText.empty()) {
            textDirty = false;
            return;
        }

        SDL_Color col = isNarrator ? COL_NARRATOR : COL_BODY_TEXT;

        int wrapWidth = static_cast<int>(textRect.w);

        SDL_Surface *surf = TTF_RenderUTF8_Blended_Wrapped(bodyFont, visibleText.c_str(), col, wrapWidth);
    }

    void rebuildNameTexture(SDL_Renderer *renderer);

    void drawRoundedRect(SDL_Renderer *renderer, SDL_FRect rect, float radius, SDL_Color color);

    void freeTextures();
};
