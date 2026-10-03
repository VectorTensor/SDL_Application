#include "scene_interface.h"
#include <memory>


template<typename T>
T& SceneManager::add_scene(std::unique_ptr<T> scene) {
    static_assert(std::is_base_of_v<Scene, T>, "T must derive from scene");

    T& ref = *scene;

    scenes[std::type_index(typeid(T))] = std::move(scene);
    return ref;
}
