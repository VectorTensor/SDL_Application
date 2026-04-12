
#include "GameObject.h"

void GameObject::AddState(const State &state) {

    states.push_back(state);

}

void GameObject::SwitchState(const char* state_name) {
    for (auto& s: states) {
        if (strcmp(s.name, state_name) == 0) {
            current_state = s;
        }
    }

}

void GameObject::Render() const {
    current_state.sprite_animator->Render();
}

