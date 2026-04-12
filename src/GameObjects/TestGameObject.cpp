//
// Created by Progressive Labs on 12/04/2026.
//

#include "TestGameObject.h"

void TestGameObject::Initialize() {
    SpriteInformation sprite = {
        "assets/warrior-packs/Fighter/Attack_1.png",
        128,
        512,
        1,
        4
    };
    SpriteAnimator sprite_animator(*mRenderer,
        {0,0,128,128},
        {0,0,128,128},
        sprite
        );


    State idle_state = {
        "idle",
        sprite_animator
    };

    AddState(idle_state);
    current_state = &states[0];



}
