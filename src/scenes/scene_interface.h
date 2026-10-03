#pragma once
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include <unordered_map>
namespace std {
    class type_index;
}
struct Context {
    SDL_Window* window;
    SDL_Renderer* renderer;
    // AssetManager& assets;   // textures, fonts, sounds (cached)
    // AudioSystem&  audio;
    // InputState&   input;
};


class Scene {
public:
    Scene(Context& ctx) : ctx(ctx) {}
    virtual ~Scene() = default;

    virtual void onEnter() {} // load assets, build UI
    virtual void onExit() {} // cleanup
    virtual void handleEvent(const SDL_Event& e) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

protected:
    Context& ctx;
};

class SceneManager {
    std::unordered_map<std::type_index, std::unique_ptr<Scene>> scenes;

public:
    template<typename T>
    T& add_scene(std::unique_ptr<T> scene);
};
