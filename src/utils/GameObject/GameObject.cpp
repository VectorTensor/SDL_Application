
#include "GameObject.h"

void GameObject::AddState(State &state) {
    states.push_back(state);
    if (current_state->name == nullptr) {

        current_state = &state;

    }

}

void GameObject::SwitchState(const char* state_name) {
    for (auto& s: states) {
        if (strcmp(s.name, state_name) == 0) {
            current_state = &s;
        }
    }

}

GameObject::GameObject(SDL_Renderer &renderer) {
    mRenderer = &renderer;
}


void GameObject::Update() {
    current_state->sprite_animator->UpdateFrame();
}

void GameObject::Render() const {
    current_state->sprite_animator->Render();
}


