#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>


typedef struct {
    SDL_FRect box;
    SDL_FRect nametag;

} VnDialogueBox;


void RenderBox(SDL_Renderer *ren, const VnDialogueBox *d);
