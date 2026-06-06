#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>


typedef struct {
    SDL_FRect rect;
    float radius;
    int thickness;
} DialogueUIAttr;

typedef struct {
    int height;
    int width;
    SDL_Texture *textTexture;

} VnDialogueBox;

void Vn_RenderBox(SDL_Renderer *ren, const VnDialogueBox *d);

void Vn_DrawRoundedRectThick(SDL_Renderer *renderer, DialogueUIAttr diagAttr);
void Vn_RenderRoundedRect(SDL_FRect rect, float radius, SDL_Renderer *ren);

void RenderGeometryTest(SDL_Renderer *ren);

void insertText(const VnDialogueBox *d_box, SDL_Renderer *ren);

void SetText(VnDialogueBox *d_box, const char *text, int size, SDL_Renderer *ren);
