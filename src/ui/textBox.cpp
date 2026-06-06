
#include "textBox.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
void Vn_RenderBox(SDL_Renderer *ren, const VnDialogueBox *d) {
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    float y_box = (float) d->height * 0.7;
    float h_box = (float) d->height * 0.3;
    SDL_FRect box = {0, y_box, (float) d->width, h_box};
    float y_name = (float) d->height * 0.65;
    float h_name = (float) d->height * 0.05;
    float w_name = (float) d->width * 0.15;
    SDL_FRect nametag = {0.0f, y_name, w_name, h_name};
    DialogueUIAttr dAttr_big = {box, 10, 4};
    DialogueUIAttr dAttr_small = {nametag, 10, 4};

    Vn_DrawRoundedRectThick(ren, dAttr_big);
    Vn_DrawRoundedRectThick(ren, dAttr_small);

    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
}


void insertText(char *text, SDL_Renderer *ren) {
    TTF_Font *font = TTF_OpenFont("monofur.ttf", 32);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surf = TTF_RenderText_Blended(font, "Hello from sdl", 25, white);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
}


void Vn_DrawRoundedRectThick(SDL_Renderer *ren, DialogueUIAttr diagAttr) {
    for (int i = 0; i < diagAttr.thickness; i++) {
        SDL_FRect r = {diagAttr.rect.x + i, diagAttr.rect.y + i, diagAttr.rect.w - i * 2, diagAttr.rect.h - i * 2};
        Vn_RenderRoundedRect(r, diagAttr.radius - i, ren);
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
