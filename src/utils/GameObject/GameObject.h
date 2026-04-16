
#ifndef SPRITEANIMATION_GAMEOBJECT_H
#define SPRITEANIMATION_GAMEOBJECT_H
#include "utils/SpriteAnimator/spriteAnimator.h"
#include <vector>

#include "utils/common/common.h"


struct State {
    const char* name;
    SpriteAnimator sprite_animator;
};

class GameObject {
protected:
    std::vector<State> states;
    SDL_Renderer* mRenderer;
    Transform transform;

public:
    int current = 0;
    void AddState(State &state);
    void SwitchState(const char* state_name);
    void Render() const;
    GameObject(SDL_Renderer &renderer);
    virtual void Initialize() = 0;
    void Update();
    void SetTransform(float x, float y, float w, float h);
    virtual void HandleInput(SDL_Event &event) = 0;




};

State CreateNewState(
    SpriteInformation sprite,
    const char* name,
    SDL_Renderer& renderer,
    Transform &transform
    );



#endif //SPRITEANIMATION_GAMEOBJECT_H
