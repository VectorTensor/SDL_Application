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
    int frameCount =0 ;
    int spriteHeight;
    int spriteWidth;
    int numRows;
    int numCols;
    int xIncrement;
    int yIncrement;

public:
    // Constructor declaration
    SpriteAnimator(
        SDL_Renderer& renderer,
        const char *asset_path,
        SDL_FRect src_rect,
        SDL_FRect dest_rect,
        int sprite_height,
        int sprite_width,
        int num_rows,
        int num_cols
            );

    // Destructor (important for cleanup)
    ~SpriteAnimator();

    void UpdateFrame();
    void Render() const;
};

#endif