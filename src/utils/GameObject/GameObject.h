
#ifndef SPRITEANIMATION_GAMEOBJECT_H
#define SPRITEANIMATION_GAMEOBJECT_H
#include "utils/SpriteAnimator/spriteAnimator.h"
#include <vector>



struct State {
    char* name;
    char* sprite_sheet_path;
    SpriteAnimator* sprite_animator;
};

class GameObject {
    std::vector<State> states;
    State current_state;

public:
    void AddState(const State &state);
    void SwitchState(const char* state_name);
    void Render() const;
    GameObject();
    ~GameObject();



};



#endif //SPRITEANIMATION_GAMEOBJECT_H
