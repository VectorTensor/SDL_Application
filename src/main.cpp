#include <SDL3/SDL.h>

#include "utils/SpriteAnimator/spriteAnimator.h"


struct SDLApplication
{
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mRunning = true;

    SDLApplication(){

        SDL_Init(SDL_INIT_VIDEO);

        SDL_CreateWindowAndRenderer("Test Window", 600, 400, SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer);


    }
    ~SDLApplication()
    {
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void MainLoop()
    {

        SDL_Event event;
        SpriteAnimator sprite_animator(*mRenderer, "assets/asset.png");

        while (mRunning)
        {
            SDL_RenderClear(mRenderer);
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    mRunning = false;

                }
                if (event.type == SDL_EVENT_KEY_DOWN) {
                    sprite_animator.UpdateFrame();
                }
            }
            sprite_animator.Render();
            SDL_RenderPresent(mRenderer);

        }

    }


};

int main(int argc, char* argv[])
{
    SDLApplication app;
    app.MainLoop();

}