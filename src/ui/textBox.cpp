
#include "textBox.h"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
void RenderBox(SDL_Renderer *ren, const VnDialogueBox *d) {
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_FRect outline = {0.0f, 0.0f, 380.0f, 220.0f};

    SDL_FRect rect = {10, 10, 500, 200};
    DrawRoundedRectThick(ren, rect, 10, 4);

    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
}

void RenderGeometryTest(SDL_Renderer *ren) {
    SDL_Vertex verts[3] = {
            {{100, 50}, {255, 0, 0, 255}, {0, 0}}, // top, red
            {{100, 150}, {0, 255, 0, 255}, {0, 0}}, // bottom-left, green
            {{150, 150}, {0, 0, 0, 255}, {0, 0}}, // bottom-right, blue
    };
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    SDL_RenderPoint(ren, 100, 50);
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderPoint(ren, 100, 150);
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    SDL_RenderPoint(ren, 150, 150);
}

void DrawRoundedRectThick(SDL_Renderer *renderer, SDL_FRect rect, float radius, int thickness) {
    for (int i = 0; i < thickness; i++) {
        SDL_FRect r = {rect.x + i, rect.y + i, rect.w - i * 2, rect.h - i * 2};
        Vn_RenderRoundedRect(r, radius - i, renderer);
    }
}

void Vn_RenderRoundedRect(SDL_FRect rect, float radius, SDL_Renderer *ren) {
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
