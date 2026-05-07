#include "DxLib.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"

#include <memory>

#include "../MouseInput/UIMouseInput.h"
#include "../AudioManager/AudioManager.h"

void GameOverScene::Initialize()
{
    bgHandle = LoadGraph("Resource/Scene/GameOverScene.png");

    AudioManager::GetInstance().StopBGM();

    // マウス表示
    SetMouseDispFlag(TRUE);

    // 最初は真っ黒
    fadeAlpha = 255;
    fadeTime = 0.0f;

    // 必要ならゲームオーバーSE
    // AudioManager::GetInstance().PlaySE("gameover");
}

void GameOverScene::Update(float dt)
{
    UIMouseInput::Update();

    // フェイドイン更新
    if (fadeTime < fadeDuration)
    {
        fadeTime += dt;

        fadeAlpha = 255 - (int)(255.0f * (fadeTime / fadeDuration));

        if (fadeAlpha < 0)
        {
            fadeAlpha = 0;
        }
    }

    // クリックでタイトルへ戻る
    if (UIMouseInput::IsLeftTriggered())
    {
        sceneManager->ChangeScene(std::make_unique<TitleScene>());
    }
}

void GameOverScene::Draw()
{
    // 背景表示
    DrawGraph(0, 0, bgHandle, TRUE);

    // 黒フェードを上から重ねる
    if (fadeAlpha > 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);

        DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}