
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
    SDL_FRect dest_rect
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
}

SpriteAnimator::~SpriteAnimator() = default;

void SpriteAnimator::UpdateFrame() {
    if (const float x_next = static_cast<float>(40 * frameCount) + mSrcRect.x; x_next >= 428-40){
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

