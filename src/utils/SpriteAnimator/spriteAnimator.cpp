
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include "utils/SpriteAnimator/spriteAnimator.h"

#include <iostream>
#include <ostream>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>

SpriteAnimator::SpriteAnimator(
    SDL_Renderer &renderer,
    const char* asset_path,
    SDL_FRect src_rect,
    SDL_FRect dest_rect,
    int sprite_height,
    int sprite_width,
    int num_rows,
    int num_cols
    )
{
    mRenderer = &renderer;
    mSurface = SDL_LoadPNG(asset_path);
    if (mSurface == nullptr) {
        SDL_Log("Failed to load image: %s", SDL_GetError());
    }
    mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
    frameCount = 1;
    mSrcRect = src_rect;
    mDestRect = dest_rect;
    spriteHeight = sprite_height;
    spriteWidth = sprite_width;
    numRows = num_rows;
    numCols = num_cols;
    xIncrement = spriteWidth/numCols;
    yIncrement = spriteHeight/numRows;
}

SpriteAnimator::~SpriteAnimator() = default;

void SpriteAnimator::UpdateFrame() {
    if (const float x_next = static_cast<float>(xIncrement * frameCount) + mSrcRect.x; x_next >= spriteWidth-xIncrement){
        frameCount = 1;
        mSrcRect.x = 0;
    }
    else {

        mSrcRect.x = x_next;
        frameCount++;
    }
}

void SpriteAnimator::Render() const {

    SDL_RenderTexture(mRenderer, mTexture, &mSrcRect, &mDestRect );
}

