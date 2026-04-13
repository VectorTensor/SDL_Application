
#include "GameObject.h"

void GameObject::AddState(State &state) {
    states.push_back(state);

}

void GameObject::SwitchState(const char* state_name) {
    for (auto& s: states) {
        if (strcmp(s.name, state_name) == 0) {
            current_state = &s;
            current_state->sprite_animator.Reset();
        }
    }

}

GameObject::GameObject(SDL_Renderer &renderer) {
    mRenderer = &renderer;
}


void GameObject::Update() {
    current_state->sprite_animator.UpdateFrame();
}

void GameObject::Render() const {
    current_state->sprite_animator.Render();
}

State CreateNewState(
    SpriteInformation sprite,
    SDL_FRect src_rect,
    SDL_FRect dest_rect,
    const char* name,
    SDL_Renderer& renderer
    ) {

    SpriteAnimator sprite_animator(renderer,
        src_rect,
        dest_rect,
        sprite
        );

    State state = {
        name,
    sprite_animator
    };

    return state;


}

