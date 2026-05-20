#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>


typedef struct {
    SDL_FRect box;
    SDL_FRect nametag;

} VnDialogueBox;


void RenderBox(SDL_Renderer *ren, const VnDialogueBox *d);

void DrawRoundedRectThick(SDL_Renderer *renderer, SDL_FRect rect, float radius, int thickness);
void Vn_RenderRoundedRect(SDL_FRect rect, float radius, SDL_Renderer *ren);

void RenderGeometryTest(SDL_Renderer *ren);
