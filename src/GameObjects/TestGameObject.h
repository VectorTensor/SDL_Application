//
// Created by Progressive Labs on 12/04/2026.
//

#ifndef SPRITEANIMATION_TESTGAMEOBJECT_H
#define SPRITEANIMATION_TESTGAMEOBJECT_H
#include "utils/GameObject/GameObject.h"


class TestGameObject: public GameObject {

public:
    void Initialize() override;
    TestGameObject(SDL_Renderer &renderer):GameObject(renderer){};
    void HandleInput(SDL_Event &event) override;

};



#endif //SPRITEANIMATION_TESTGAMEOBJECT_H
