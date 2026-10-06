#include <vector>
#include "scenes.h"


void setup_main_menu_scene(std::vector<Scene>& scenes, SDL_Window* window, SDL_Renderer* renderer) {
    auto ui_manager = UIManager();
    ui_manager.add_button(Button("assets/ui_assets/VisualNovelDialogueGUI_PNG/namebox_2_green.png", renderer)

    );
    const auto context = Context{window, renderer, ui_manager};

    const auto scene = create_scene("main menu", context);

    scenes.push_back(*scene);
    delete scene;
}
