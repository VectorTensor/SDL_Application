#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include "common/RenderData.h"


typedef struct {
    SDL_FRect rect;
    float radius;
    int thickness;
} DialogueUIAttr;


typedef enum { ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT } HAlign;
typedef enum { ALIGN_TOP, ALIGN_MIDDLE, ALIGN_BOTTOM } VAlign;


void DrawRoundedRectangleThick(SDL_Renderer *renderer, const DialogueUIAttr *diagAttr);
void renderRoundedRectangle(SDL_FRect rect, float radius, SDL_Renderer *ren);

void RenderGeometryTest(SDL_Renderer *ren);


typedef struct {
    char text[2000];
    bool enabled; // controls visibility
    TTF_Font *font;
    char speaker[100];
    DialogueUIAttr boxProps;
    DialogueUIAttr nameProps;
    HAlign ha;
    VAlign va;
} TextBox;

void RenderTextBox(TextBox *b, SDL_Renderer *ren, const WorldData *w);
void SetText(TextBox *t, const char *text, size_t size, SDL_Renderer *ren, const WorldData *w);
