#pragma once
#include <SDL3/SDL_render.h>
#include <string>
#include <vector>

#include "common/RenderData.h"
#include "utils/common/common.h"

class Button {
public:
    explicit Button(std::string button_asset, SDL_Renderer* renderer, SDL_Window* window, const GameData& g_data);
    void setPosition(const Transform2&);
    void RenderButton();
    void setRelativePosition(int rel_x, int rel_y);

private:
    Transform2 transform;

    Transform2 transform_relative;

    SDL_Renderer* renderer;

    SDL_Texture* texture;

    SDL_Window* window;
    GameData g_data;
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
