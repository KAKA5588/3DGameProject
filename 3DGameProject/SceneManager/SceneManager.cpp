#include "SceneManager.h"
#include "Scene.h"

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
    // 即切り替えせず予約
    nextScene = std::move(newScene);
}

void SceneManager::Update(float dt)
{
    // シーン切り替え処理（安全）
    if (nextScene)
    {
        currentScene = std::move(nextScene);
        currentScene->SetSceneManager(this);
        currentScene->Initialize();
    }

    if (currentScene)
        currentScene->Update(dt);
}

void SceneManager::Draw()
{
    if (currentScene)
        currentScene->Draw();
}