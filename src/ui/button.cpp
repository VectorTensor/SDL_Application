


#include <SDL3/SDL_log.h>
#include <utility>

#include "common/RenderData.h"
#include "ui_elements.h"

Button::Button(std::string button_asset, SDL_Renderer* renderer, SDL_Window* window, const GameData& g_data) {
    this->renderer = renderer;
    this->button_asset = std::move(button_asset);
    this->window = window;
    this->g_data = g_data;
    this->CreateTexture();
}
void Button::setPosition(const Transform2& transform_a) {
    this->transform = transform_a;
    RenderButton();
}

Transform2 get_absolute_transform(int rel_x, int rel_y, const GameData& g_data) {
    int game_height = *g_data.height_p;
    int game_width = *g_data.width_p;
    Transform2 transform;

    transform.x = (game_width * rel_x) / 100.0;
    transform.y = (game_height * rel_y) / 100.0;
    return transform;
}

void Button::setRelativePosition(int rel_x, int rel_y) {
    transform_relative = {(float) rel_x, (float) rel_y};
    RenderButton();
}


void Button::CreateTexture() {
    auto mSurface = SDL_LoadPNG(this->button_asset.c_str());
    if (!mSurface) {
        SDL_Log("SDL_LoadPNG failed: %s", SDL_GetError());
        return;
    }
    this->texture = SDL_CreateTextureFromSurface(this->renderer, mSurface);
    height = mSurface->h;
    width = mSurface->w;

    SDL_DestroySurface(mSurface);
}


void Button::RenderButton() {
    this->transform = get_absolute_transform(transform_relative.x, transform_relative.y, this->g_data);
    auto srcRect = SDL_FRect{

            0, 0, (float) width, (float) height

    };

    auto distRect = SDL_FRect{

            transform.x, transform.y, (float) width, (float) height};
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
