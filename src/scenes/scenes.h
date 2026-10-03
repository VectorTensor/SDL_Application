#include "scenes/scene_interface.h"

class MainMenuScene : public Scene {
public:
    explicit MainMenuScene(Context& ctx);
    void onEnter() override;
    void onExit() override;
    void handleEvent(const SDL_Event& e) override;
    void update(float dt) override;
    void render() override;

private:
    int selectedItem = 0;
};
