#pragma once
#include <memory>

class Scene;

class SceneManager
{
public:
    void ChangeScene(std::unique_ptr<Scene> newScene);
    void Update(float dt);
    void Draw();

private:
    std::unique_ptr<Scene> currentScene = nullptr;
    std::unique_ptr<Scene> nextScene = nullptr;
    bool firstFrame = true;
};