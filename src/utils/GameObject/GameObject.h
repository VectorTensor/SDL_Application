
#ifndef SPRITEANIMATION_GAMEOBJECT_H
#define SPRITEANIMATION_GAMEOBJECT_H
#include "utils/SpriteAnimator/spriteAnimator.h"
#include <vector>



struct State {
    const char* name;
    SpriteAnimator sprite_animator;
};

class GameObject {
protected:
    std::vector<State> states;
    SDL_Renderer* mRenderer;

public:
    int current = 0;
    void AddState(State &state);
    void SwitchState(const char* state_name);
    void Render() const;
    GameObject(SDL_Renderer &renderer);
    virtual void Initialize() = 0;
    void Update();



};

State CreateNewState(
    SpriteInformation sprite,
    SDL_FRect scr_rect,
    SDL_FRect dest_rect,
    const char* name,
    SDL_Renderer& renderer
    );



#endif //SPRITEANIMATION_GAMEOBJECT_H
