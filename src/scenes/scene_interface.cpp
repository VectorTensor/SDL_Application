#include "scene_interface.h"


Scene* create_scene(const std::string& name, const Context& ctx) {
    return new Scene{.ctx = ctx, .name = name};
}

void render_scene(Scene& scene) {
    scene.ctx.ui_manager.render_ui();
}


void render_scenes(std::vector<Scene>& scenes) {
    for (auto& s: scenes) {
        render_scene(s);
    }
}
