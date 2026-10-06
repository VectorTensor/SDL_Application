#pragma once
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

#include "ui/ui_elements.h"

struct Context {
    SDL_Window* window;
    SDL_Renderer* renderer;
    // AssetManager& assets;   // textures, fonts, sounds (cached)
    // AudioSystem&  audio;
    // InputState&   input;
    UIManager ui_manager;
};


struct Scene {
    Context ctx = {};
    std::string name;
};


Scene* create_scene(const std::string& name, const Context& ctx);


void render_scenes(std::vector<Scene>& scenes);
