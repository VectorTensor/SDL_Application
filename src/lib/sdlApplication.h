
#ifndef SPRITEANIMATION_SDLAPPLICATION_H
#define SPRITEANIMATION_SDLAPPLICATION_H
#include <SDL3/SDL_render.h>
#include <vector>

#include "ui/textBox.h"
#include "utils/GameObject/GameObject.h"
#include "utils/SpriteAnimator/spriteAnimator.h"


class SDLApplication {
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    bool mRunning = true;
    std::vector<SpriteAnimator> sprite_animators;
    std::vector<GameObject *> game_objects;
    int height;
    int width;
    VnDialogueBox test;

public:
    SDLApplication();
    void push_sprite_animator(const SpriteAnimator &sprite_animator);
    ~SDLApplication();
    void Tick();
    void Input();
    void Update();
    void Render();
    void MainLoop();
};


#endif // SPRITEANIMATION_SDLAPPLICATION_H
