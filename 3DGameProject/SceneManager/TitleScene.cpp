#include "DxLib.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <memory>
#include "../MouseInput/UIMouseInput.h"

void TitleScene::Initialize()
{
    TitleHandle = LoadGraph("Resource/Scene/TitleScene.png");
}

void TitleScene::Update(float dt)
{
    // UIマウス更新
    UIMouseInput::Update();

    // 左クリックでゲームへ
    if (UIMouseInput::IsLeftTriggered())
    {
        sceneManager->ChangeScene(std::make_unique<GameScene>());
    }
}

void TitleScene::Draw()
{
    DrawGraph(0, 0, TitleHandle, TRUE);
}