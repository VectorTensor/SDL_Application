
#include "textBox.h"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
void RenderBox(SDL_Renderer *ren, const VnDialogueBox *d) {
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_FRect outline = {0.0f, 0.0f, 380.0f, 220.0f};
    Vn_RenderRoundedRect(10.0, 200, 500, 10, 10, ren);
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
}

void Vn_RenderRoundedRect(float radius, float height, float width, float x, float y, SDL_Renderer *ren) {
    auto h = height;
    auto w = width;
    auto r = radius;
    r = fminf(h / 2, fminf(r, w / 2));

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
