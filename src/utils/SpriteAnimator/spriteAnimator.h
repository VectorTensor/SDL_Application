#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H

#include <string>
#include <SDL3/SDL_render.h>

class SpriteAnimator {
private:
    SDL_Surface* mSurface;
    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
    SDL_FRect mSrcRect;
    SDL_FRect mDestRect;
    int frameCount;

public:
    // Constructor declaration
    SpriteAnimator(SDL_Renderer& renderer, const char *asset_path);

    // Destructor (important for cleanup)
    ~SpriteAnimator();

    void UpdateFrame();
    void Render() const;
};

#endif