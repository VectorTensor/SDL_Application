#include <vector>
#include "scenes.h"


void setup_main_menu_scene(std::vector<Scene>& scenes, SDL_Window* window, SDL_Renderer* renderer,
                           const GameData& game_data) {
    auto ui_manager = UIManager();
    Button button("assets/ui_assets/VisualNovelDialogueGUI_PNG/namebox_2_green.png", renderer, window, game_data);
    button.setRelativePosition(50, 50);
    ui_manager.add_button(button);
    const auto context = Context{window, renderer, ui_manager};

    const auto scene = create_scene("main menu", context);

    scenes.push_back(*scene);
    delete scene;
}
