#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H

#include <SDL3/SDL_render.h>

#include "utils/common/common.h"


struct SpriteInformation {
    char* sprite_path;
    int num_rows;
    int num_cols;
    int sprite_height = 0;
    int sprite_width = 0;
};

class SpriteAnimator {
    SDL_Surface* mSurface;
    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
    int frameCount = 0;
    int spriteHeight;
    int spriteWidth;
    int numRows;
    int numCols;
    int xIncrement;
    int yIncrement;
    int frameTimeMs = 200;
    float currentTime = 0;

public:
    SDL_FRect mSrcRect;
    SDL_FRect mDestRect;
    // Constructor declaration
    SpriteAnimator(SDL_Renderer& renderer, SpriteInformation sprite_information);

    // Destructor (important for cleanup)
    ~SpriteAnimator();

    void UpdateFrame();
    void Render() const;
    void Reset();

    void ResetTransform(Transform transform);
};

#endif
