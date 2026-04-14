
#include "sdlApplication.h"

#include <format>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>

#include "GameObjects/TestGameObject.h"
#include "utils/GameObject/GameObject.h"

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
            // for (auto& s: sprite_animators) {
            //     s.UpdateFrame();
            // }
            if (event.key.key == SDLK_RETURN) {
                game_objects[0]->SwitchState("fight");
            }
            else if (event.key.key == SDLK_SPACE) {
                game_objects[0]->SwitchState("jump");
            }
            else if (event.key.key == SDLK_W) {
                game_objects[0]->SwitchState("walk");
            }
        }
    }
}
void SDLApplication::Update() {
    for (auto& g: game_objects) {
        g->Update();
    }
}

void SDLApplication::Render() {
    SDL_RenderClear(mRenderer);
    // for (auto& s: sprite_animators) {
    //     s.Render();
    // }
    for (auto& g: game_objects) {
        g->Render();
    }
    SDL_RenderPresent(mRenderer);
}

void SDLApplication::MainLoop()
{

    Uint64 lastTime = 0;
    Uint64 fps= 0;
    TestGameObject test_game_object(*mRenderer);
    test_game_object.Initialize();
    game_objects.push_back(&test_game_object);


    while (mRunning)
    {
        Uint64 currentTick = SDL_GetTicks();
        Tick();
        fps++;
        Uint64 deltaTime = SDL_GetTicks() - currentTick;
        if (currentTick > lastTime + 1000) {

            lastTime = currentTick;
            std::string title;
            title = std::format("FPS: {}",  std::to_string(fps));

            SDL_SetWindowTitle(mWindow, title.c_str());
            fps = 0;
        }


    }

}



