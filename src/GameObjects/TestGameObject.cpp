//
// Created by Progressive Labs on 12/04/2026.
//

#include "TestGameObject.h"

void TestGameObject::Initialize() {
    auto fight_state = CreateNewState(
        {"assets/warrior-packs/Fighter/Attack_1.png",
            128,
            512,
            1,
            4 },
        {0,0,128,128},
        {0,0,128,128},
        "fight",
        *mRenderer
        );
    AddState(fight_state);

    auto jump_state= CreateNewState(
        {"assets/warrior-packs/Fighter/Jump.png",
            128,
            1280,
            1,
            10 },
        {0,0,128,128},
        {0,0,128,128},
        "jump",
        *mRenderer
        );
    AddState(jump_state);

    current_state = &states[1];


}
