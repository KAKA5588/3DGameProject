#include "GameScene.h"
#include "../AudioManager/AudioManager.h"

GameScene::~GameScene() = default;

void GameScene::Initialize()
{
    AudioManager::GetInstance().Initialize();
    //âπó í≤êﬂ
    AudioManager::GetInstance().SetBGMVolume(90);
    AudioManager::GetInstance().SetSEVolume(SECategory::FootStep, 180);

    stage = std::make_unique<Stage>();
    player = std::make_unique<Player>();
    enemy = std::make_unique<Enemy>();
    camera = std::make_unique<Camera>();

    camera->SetTarget(player.get());
    player->SetCamera(camera.get());
    player->SetStage(stage.get());
    camera->SetStage(stage.get());
    enemy->SetStage(stage.get());

    // objectsÇÕÅuéQè∆ÇæÇØÅv
    objects =
    {
        stage.get(),
        player.get(),
        enemy.get(),
        camera.get()
    };

    for (auto obj : objects)
        obj->Initialize();

    AudioManager::GetInstance().PlayBGM(BGMType::GamaSceneBGM);
}

void GameScene::Update(float dt)
{
    enemy->SetPlayerPos(player->GetPosition());

    for (auto obj : objects)
        obj->Update(dt);

    camera->Apply();
}

void GameScene::Draw()
{
    for (auto obj : objects)
        obj->Draw();
}