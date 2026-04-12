//
// Created by Progressive Labs on 12/04/2026.
//

#include "TestGameObject.h"

void TestGameObject::Initialize() {

    SpriteAnimator sprite_animator(*mRenderer,
        "assets/warrior-packs/Fighter/Idle.png",
        {0,0,128,128},
        {0,0,128,128},
        128,
        768,
        1,
        6
        );


    State idle_state = {
        "idle",
        &sprite_animator
    };

    AddState(idle_state);



}
