#pragma once
#include <memory>

class SceneManager;

class Scene
{
public:
    virtual ~Scene() = default;

    void SetSceneManager(SceneManager* manager)
    {
        sceneManager = manager;
    }

    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

protected:
    SceneManager* sceneManager = nullptr;
};