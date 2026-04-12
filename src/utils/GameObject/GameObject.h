
#ifndef SPRITEANIMATION_GAMEOBJECT_H
#define SPRITEANIMATION_GAMEOBJECT_H
#include "utils/SpriteAnimator/spriteAnimator.h"
#include <vector>



struct State {
    char* name;
    SpriteAnimator* sprite_animator;
};

class GameObject {
protected:
    std::vector<State> states;
    State* current_state;
    SDL_Renderer* mRenderer;

public:
    void AddState(State &state);
    void SwitchState(const char* state_name);
    void Render() const;
    GameObject(SDL_Renderer &renderer);
    virtual void Initialize() = 0;
    void Update();



};



#endif //SPRITEANIMATION_GAMEOBJECT_H
