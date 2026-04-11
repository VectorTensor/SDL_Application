#include <SDL3/SDL.h>

#include "utils/SpriteAnimator/spriteAnimator.h"
#include <vector>


struct SDLApplication
{
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mRunning = true;
    std::vector<SpriteAnimator> sprite_animators;

    SDLApplication() {

        SDL_Init(SDL_INIT_VIDEO);

        SDL_CreateWindowAndRenderer("Test Window", 600, 400, SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer);


    }
    void push_sprite_animator(const SpriteAnimator& sprite_animator) {
        sprite_animators.push_back(sprite_animator);
    }
    ~SDLApplication()
    {
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void Tick() {

        SDL_Event event;
        SDL_RenderClear(mRenderer);
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
        for (auto& s: sprite_animators) {
            s.Render();
        }
        SDL_RenderPresent(mRenderer);


    }

    void MainLoop()
    {

        SpriteAnimator sprite_animator(*mRenderer, "assets/asset.png");
        push_sprite_animator(sprite_animator);

        while (mRunning)
        {
            Tick();

        }

    }


};

int main(int argc, char* argv[])
{
    SDLApplication app;
    app.MainLoop();

}