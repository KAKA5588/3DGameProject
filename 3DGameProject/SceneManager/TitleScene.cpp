#include "DxLib.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <memory>
#include "../MouseInput/UIMouseInput.h"
#include "../AudioManager/AudioManager.h"

void TitleScene::Initialize()
{
    AudioManager::GetInstance().Initialize();
    //音量調節
    AudioManager::GetInstance().SetBGMVolume(90);

    TitleHandle = LoadGraph("Resource/Scene/TitleScene.png");
    GolemHandle = LoadGraph("Resource/Scene/SceneChase.png");

    AudioManager::GetInstance().PlayBGM(BGMType::TitleSceneBGM);
}

void TitleScene::Update(float dt)
{
    UIMouseInput::Update();

    switch (state)
    {
    case TitleState::Idle:
        if (UIMouseInput::IsLeftTriggered())
        {
            state = TitleState::FadeOut;
            fadeTime = 0.0f;
        }
        break;

    case TitleState::FadeOut:
        fadeTime += dt;

        fadeAlpha = (int)(255.0f * (fadeTime / fadeDuration));

        if (fadeTime >= fadeDuration)
        {
            state = TitleState::ShowGolem;
        }
        break;

    case TitleState::ShowGolem:
        sceneManager->ChangeScene(std::make_unique<GameScene>());
        break; 
    }
}

void TitleScene::Draw()
{
    switch (state)
    {
    case TitleState::Idle:
        // クリック前：タイトルだけ
        DrawGraph(0, 0, TitleHandle, TRUE);
        break;

    case TitleState::FadeOut:
        // タイトル＋フェード
        DrawGraph(0, 0, TitleHandle, TRUE);

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
        DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        break;

    case TitleState::ShowGolem:
        // ここだけゴーレム（タイトル完全非表示）
        DrawGraph(0, 0, GolemHandle, TRUE);
        break;
    }
}