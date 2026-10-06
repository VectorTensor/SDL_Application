


#include <SDL3/SDL_log.h>
#include <utility>

#include "ui_elements.h"

Button::Button(std::string button_asset, SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->button_asset = std::move(button_asset);
    this->CreateTexture();
}

void Button::CreateTexture() {
    auto mSurface = SDL_LoadPNG(this->button_asset.c_str());
    if (!mSurface) {
        SDL_Log("SDL_LoadPNG failed: %s", SDL_GetError());
        return;
    }
    this->texture = SDL_CreateTextureFromSurface(this->renderer, mSurface);
    SDL_DestroySurface(mSurface);
}


void Button::RenderButton() const {
    auto srcRect = SDL_FRect{

            0, 0, 1000, 1000

    };

    auto distRect = SDL_FRect{

            0, 0, 100, 100

    };
    if (!SDL_RenderTexture(renderer, this->texture, &srcRect, &distRect)) {
        SDL_Log("SDL_RenderTexture failed: %s", SDL_GetError());
    }
}


void UIManager::add_button(const Button& button) {
    buttons.push_back(button);
}

void UIManager::render_ui() {
    for (auto& b: this->buttons) {
        b.RenderButton();
    }
}
