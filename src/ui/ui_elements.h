#pragma once
#include <SDL3/SDL_render.h>
#include <string>
#include <vector>
#include "utils/common/common.h"

class Button {
public:
    explicit Button(std::string button_asset, SDL_Renderer* renderer);
    void setPosition(Transform2);
    void RenderButton() const;

private:
    Transform2 transform;

    SDL_Renderer* renderer;

    SDL_Texture* texture;

    std::string button_asset;
    int height;
    int width;

    void CreateTexture();
};


class UIManager {
public:
    void add_button(const Button& button);
    void render_ui();

private:
    std::vector<Button> buttons;
};
