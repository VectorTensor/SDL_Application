//
// Created by Progressive Labs on 12/04/2026.
//

#include "sdlApplication.h"

#include <format>
#include <SDL3/SDL_timer.h>

SDLApplication::SDLApplication() {

        SDL_Init(SDL_INIT_VIDEO);

        SDL_CreateWindowAndRenderer("Test Window", 600, 400, SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer);


}
void SDLApplication::push_sprite_animator(const SpriteAnimator& sprite_animator) {
        sprite_animators.push_back(sprite_animator);
}
SDLApplication::~SDLApplication(){
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void SDLApplication::Tick() {

    Input();
    Update();
    Render();

}

void SDLApplication::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            mRunning = false;

        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            for (auto& s: sprite_animators) {
                s.UpdateFrame();
            }
        }
    }
}
void SDLApplication::Update() {

}

void SDLApplication::Render() {
    SDL_RenderClear(mRenderer);
    for (auto& s: sprite_animators) {
        s.Render();
    }
    SDL_RenderPresent(mRenderer);
}

void SDLApplication::MainLoop()
{

    SpriteAnimator sprite_animator(*mRenderer,
        "assets/asset.png",
        {0,0,40,40},
        {0,0,120,120});
    push_sprite_animator(sprite_animator);
    Uint64 frames = 0;
    Uint64 lastTime = 0;
    Uint64 fps= 0;

    while (mRunning)
    {
        Uint64 currentTick = SDL_GetTicks();
        Tick();
        frames ++;
        fps++;
        Uint64 deltaTime = SDL_GetTicks() - currentTick;
        if (currentTick > lastTime + 1000) {

            lastTime = currentTick;
            frames = 0;
            std::string title;
            title = std::format("FPS: {}",  std::to_string(fps));

            SDL_SetWindowTitle(mWindow, title.c_str());
            fps = 0;
        }


    }

}



