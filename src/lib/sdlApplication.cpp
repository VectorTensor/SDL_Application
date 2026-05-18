#include "sdlApplication.h"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <format>

#include "GameObjects/TestGameObject.h"
#include "utils/GameObject/GameObject.h"

SDLApplication::SDLApplication() {
    SDL_Init(SDL_INIT_VIDEO);
    height = 400;
    width = 600;

    SDL_CreateWindowAndRenderer("Test Window", width, height, SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer);
}

void SDLApplication::push_sprite_animator(const SpriteAnimator &sprite_animator) {
    sprite_animators.push_back(sprite_animator);
}

SDLApplication::~SDLApplication() {
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
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            mRunning = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            for (auto &g: game_objects) {
                g->HandleInput(event);
            }
        }

        if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            width = event.window.data1;
            height = event.window.data2;
        }
    }
}

void SDLApplication::Update() {
    for (auto &g: game_objects) {
        g->Update();
    }
}

void SDLApplication::Render() {
    SDL_SetRenderDrawColor(mRenderer, 30, 30, 30, 255); // dark gray background
    SDL_RenderClear(mRenderer);
    // for (auto& s: sprite_animators) {
    //     s.Render();
    // }
    // for (auto &g: game_objects) {
    //     g->Render();
    // }
    // RenderBox(mRenderer, &this->test);
    // Step 2: NOW set green and draw the rect
    RenderBox(mRenderer, &this->test);
    SDL_RenderPresent(mRenderer);
}

void SDLApplication::MainLoop() {
    Uint64 lastTime = 0;
    Uint64 fps = 0;
    TestGameObject *test_game_object = new TestGameObject(*mRenderer);
    test_game_object->Initialize();
    game_objects.push_back(test_game_object);

    SDL_FRect box = {130.0f, 130.0f, 380.0f, 220.0f};

    this->test.box = box;


    while (mRunning) {
        Uint64 currentTick = SDL_GetTicks();
        Tick();
        fps++;
        Uint64 deltaTime = SDL_GetTicks() - currentTick;
        if (currentTick > lastTime + 1000) {
            lastTime = currentTick;
            std::string title;
            title = std::format("FPS: {}", std::to_string(fps));

            SDL_SetWindowTitle(mWindow, title.c_str());
            fps = 0;
        }
    }

    delete test_game_object;
}
