
#include "textBox.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <cmath>
#include <cstring>

#include "utils/common/common.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
void SetText(const SDL_FRect *boxRect, const char *text, size_t size, SDL_Renderer *ren, const WorldData *world,
             const VAlign va, const HAlign ha) {
    const float multipleX = static_cast<float>(world->width) / static_cast<float>(REFERENCE_X);
    const float multipleY = static_cast<float>(world->height) / static_cast<float>(REFERENCE_Y);
    const float maxValue = std::max(multipleX, multipleY);
    const int fontSize = maxValue * 30;


    TTF_Font *font = TTF_OpenFont("assets/fonts/monofur.ttf", static_cast<float>(fontSize));
    if (font == nullptr) {
        const auto error = SDL_GetError();
        SDL_Log("Font not found %s", error);
    }
    int tw, th;
    TTF_GetStringSize(font, text, 0, &tw, &th);
    float x = 0;
    auto box_rect = boxRect;
    switch (ha) {
        case ALIGN_LEFT:
            x = x;
            break;
        case ALIGN_CENTER:
            x = x + (box_rect->w - static_cast<float>(tw)) / 2.0f;
            break;
        case ALIGN_RIGHT:
            x = x + box_rect->w - static_cast<float>(tw);
            break;
    }

    float y;
    switch (va) {
        case ALIGN_TOP:
            y = box_rect->y;
            break;
        case ALIGN_MIDDLE:
            y = box_rect->y + (box_rect->h - th) / 2.0f;
            break;
        case ALIGN_BOTTOM:
            y = box_rect->y + box_rect->h - th;
            break;
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surf = TTF_RenderText_Blended(font, text, size, white);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    float w, h;
    SDL_GetTextureSize(tex, &w, &h);
    SDL_FRect dst = {x, y, w, h};
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderTexture(ren, tex, nullptr, &dst);
}


void DrawRoundedRectangleThick(SDL_Renderer *ren, const DialogueUIAttr *diagAttr) {
    for (int i = 0; i < diagAttr->thickness; i++) {
        SDL_FRect r = {diagAttr->rect.x + i, diagAttr->rect.y + i, diagAttr->rect.w - i * 2, diagAttr->rect.h - i * 2};
        renderRoundedRectangle(r, diagAttr->radius - i, ren);
    }
}

void renderRoundedRectangle(SDL_FRect rect, float radius, SDL_Renderer *ren) {
    auto h = rect.h;
    auto w = rect.w;
    auto r = radius;
    r = fminf(h / 2, fminf(r, w / 2));
    float x = rect.x;
    float y = rect.y;

    // Draw lines top bottom left right
    SDL_RenderLine(ren, x + r, y, x + w - r, y);
    SDL_RenderLine(ren, x + r, y + h, x + w - r, y + h);
    SDL_RenderLine(ren, x, y + r, x, y + h - r);
    SDL_RenderLine(ren, x + w, y + r, x + w, y + h - r);

    float ctl_x = x + r;
    float ctl_y = y + r;
    float ctr_x = x + w - r;
    float ctr_y = y + r;
    float cbl_x = x + r;
    float cbl_y = y + h - r;
    float cbr_x = x + w - r;
    float cbr_y = y + h - r;


    for (int angle = 0; angle <= 90; angle++) {
        float dx = cos(angle * (M_PI / 180.0)) * r;
        float dy = sin(angle * (M_PI / 180.0)) * r;

        // top left
        SDL_RenderPoint(ren, ctl_x - dx, ctl_y - dy);
        // top right
        SDL_RenderPoint(ren, ctr_x + dx, ctr_y - dy);
        // bottom left
        SDL_RenderPoint(ren, cbl_x - dx, cbl_y + dy);
        // bottom right
        SDL_RenderPoint(ren, cbr_x + dx, cbr_y + dy);
    }
}

void RenderTextBox(TextBox *b, SDL_Renderer *ren, const WorldData *w) {
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    const float y_box = static_cast<float>(w->height) * 0.7f;
    const float h_box = static_cast<float>(w->height) * 0.3f;
    const SDL_FRect box = {0, y_box, static_cast<float>(w->width), h_box};
    const float y_name = static_cast<float>(w->height) * 0.65f;
    const float h_name = static_cast<float>(w->height) * 0.05f;
    const float w_name = static_cast<float>(w->width) * 0.15f;
    const SDL_FRect nametag = {0.0f, y_name, w_name, h_name};
    b->boxProps = {box, 10, 2};
    b->nameProps = {nametag, 10, 2};

    DrawRoundedRectangleThick(ren, &b->boxProps);
    DrawRoundedRectangleThick(ren, &b->nameProps);

    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);

    SetText(&b->boxProps.rect, b->text, strlen(b->text), ren, w, b->va, b->ha);
    SetText(&b->nameProps.rect, b->speaker, strlen(b->speaker), ren, w, b->va, b->ha);
}
