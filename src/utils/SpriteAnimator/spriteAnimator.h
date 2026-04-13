#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H

#include <string>
#include <SDL3/SDL_render.h>

struct SpriteInformation{
    char* sprite_path;
    int sprite_height;
    int sprite_width;
    int num_rows;
    int num_cols;

};

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
    int frameTimeMs = 500;
    float currentTime = 0;

public:
    // Constructor declaration
    SpriteAnimator(
        SDL_Renderer& renderer,
        SDL_FRect src_rect,
        SDL_FRect dest_rect,
        SpriteInformation sprite_information
        );

    // Destructor (important for cleanup)
    ~SpriteAnimator();

    void UpdateFrame();
    void Render() const;
    void Reset();
};

#endif