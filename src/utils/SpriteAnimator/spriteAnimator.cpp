
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include "utils/SpriteAnimator/spriteAnimator.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_timer.h>

SpriteAnimator::SpriteAnimator(
    SDL_Renderer &renderer,
    SpriteInformation sprite_information
    )
{
    mRenderer = &renderer;
    mSurface = SDL_LoadPNG(sprite_information.sprite_path);
    if (mSurface == nullptr) {
        SDL_Log("Failed to load image: %s", SDL_GetError());
    }else {
        sprite_information.sprite_height = mSurface->h;
        sprite_information.sprite_width = mSurface->w;
    }
    mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
    frameCount = 0;
    spriteHeight = sprite_information.sprite_height;
    spriteWidth = sprite_information.sprite_width;
    numRows = sprite_information.num_rows;
    numCols = sprite_information.num_cols;
    xIncrement = spriteWidth/numCols;
    yIncrement = spriteHeight/numRows;
    mSrcRect = {0,0,static_cast<float>(xIncrement),static_cast<float>(yIncrement)};
}

SpriteAnimator::~SpriteAnimator() = default;

void SpriteAnimator::UpdateFrame() {
    auto deltaTime = SDL_GetTicks() - currentTime;
    if (deltaTime > frameTimeMs) {
        currentTime = SDL_GetTicks();
        const float x_next = static_cast<float>(xIncrement * frameCount) + mSrcRect.x;
        if ( x_next >= spriteWidth){
            frameCount = 0;
            mSrcRect.x = 0;
        }
        else {

            mSrcRect.x = x_next;
            frameCount++;
        }
    }

    }

void SpriteAnimator::Render() const {

    SDL_RenderTexture(mRenderer, mTexture, &mSrcRect, &mDestRect );
}

void SpriteAnimator::Reset() {
    mSrcRect.x = 0;
}

void SpriteAnimator::ResetTransform(const Transform transform) {
    mDestRect.x = transform.x;
    mDestRect.y = transform.y;

    mDestRect.w = transform.w;
    mDestRect.h = transform.h;
}

