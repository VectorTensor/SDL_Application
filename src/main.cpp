#include <SDL3/SDL.h>


struct SDLApplication
{
    SDL_Window* mWindow;
    bool mRunning = true;

    SDLApplication()
    {

        SDL_Init(SDL_INIT_VIDEO);

        mWindow = SDL_CreateWindowAndRenderer("Test Window", 600, 400, SDL_WINDOW_RESIZABLE, &window, &renderer);


    }
    ~SDLApplication()
    {
        SDL_Quit();
    }

    void MainLoop()
    {

        SDL_Event event;

        while (mRunning)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    mRunning = false;

                }
            }
        }

    }


};

int main(int argc, char* argv[])
{
    SDL_Log("Hello World");

}