
#include "GameObject.h"

void GameObject::AddState(State &state) {
    states.push_back(state);

}

void GameObject::SwitchState(const char* state_name) {
    int count = 0;
    for (auto& s: states) {
        if (strcmp(s.name, state_name) == 0) {
            current = count;
            states[current].sprite_animator.Reset();
            states[current].sprite_animator.ResetTransform(transform);
        }
        count++;
    }

}

GameObject::GameObject(SDL_Renderer &renderer) {
    mRenderer = &renderer;
}


void GameObject::Update() {
    states[current].sprite_animator.UpdateFrame();
}


void GameObject::SetTransform(float x, float y, float w, float h) {
    transform.x = x;
    transform.y = y;
    transform.w = w;
    transform.h = h;

    states[current].sprite_animator.mDestRect.x = x;

    states[current].sprite_animator.mDestRect.y = y;

    states[current].sprite_animator.mDestRect.w = w;
    states[current].sprite_animator.mDestRect.h = h;

}

void GameObject::Render() const {
    states[current].sprite_animator.Render();
}

State CreateNewState(
    SpriteInformation sprite,
    const char* name,
    SDL_Renderer& renderer,
    Transform &transform
    ) {

    SpriteAnimator sprite_animator(renderer, sprite);
    sprite_animator.mDestRect.x = transform.x;
    sprite_animator.mDestRect.y = transform.y;
    sprite_animator.mDestRect.w = transform.w;
    sprite_animator.mDestRect.h = transform.h;

    State state = {
        name,
    sprite_animator
    };

    return state;


}

