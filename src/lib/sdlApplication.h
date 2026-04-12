//
// Created by Progressive Labs on 12/04/2026.
//

#ifndef SPRITEANIMATION_SDLAPPLICATION_H
#define SPRITEANIMATION_SDLAPPLICATION_H
#include <vector>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>

#include "utils/SpriteAnimator/spriteAnimator.h"


class SDLApplication
{
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mRunning = true;
    std::vector<SpriteAnimator> sprite_animators;
public:
    SDLApplication();
    void push_sprite_animator(const SpriteAnimator& sprite_animator);
    ~SDLApplication();
    void Tick() ;
    void Input() ;
    void Update() ;
    void Render() ;
    void MainLoop()  ;

};



#endif //SPRITEANIMATION_SDLAPPLICATION_H
