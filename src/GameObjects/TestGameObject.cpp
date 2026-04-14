//
// Created by Progressive Labs on 12/04/2026.
//

#include "TestGameObject.h"

void TestGameObject::Initialize() {
    transform.x = 0;
    transform.y = 0;
    transform.w = 128,
    transform.h = 128;
    auto fight_state = CreateNewState(
        {"assets/warrior-packs/Fighter/Attack_1.png",
            1,
            4 },
        "fight",
        *mRenderer,
        transform
        );
    AddState(fight_state);

    auto jump_state= CreateNewState(
        {"assets/warrior-packs/Fighter/Jump.png",
            1,
            10 },
        "jump",
        *mRenderer,
        transform
        );
    AddState(jump_state);

    current = 1;


}
