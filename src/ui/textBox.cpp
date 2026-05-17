
#include "textBox.h"


void RenderBox(SDL_Renderer *ren, const VnDialogueBox *d) {
    SDL_FRect rect = {100.0f, 100.0f, 440.0f, 280.0f};
    SDL_RenderFillRect(ren, &rect);
    SDL_FRect outline = {130.0f, 130.0f, 380.0f, 220.0f};
    SDL_RenderRect(ren, &outline);
}
