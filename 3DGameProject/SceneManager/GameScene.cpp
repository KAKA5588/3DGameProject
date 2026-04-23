#include "GameScene.h"
//
#include "../AudioManager/AudioManager.h"

GameScene::~GameScene() = default;

void GameScene::Initialize()
{
    AudioManager::GetInstance().Initialize();

    stage = std::make_unique<Stage>();
    player = std::make_unique<Player>();
    enemy = std::make_unique<Enemy>();
    camera = std::make_unique<Camera>();

    camera->SetTarget(player.get());
    player->SetCamera(camera.get());
    player->SetStage(stage.get());
    camera->SetStage(stage.get());
    enemy->SetStage(stage.get());

    // objects‚ÍuŽQÆ‚¾‚¯v
    objects =
    {
        stage.get(),
        player.get(),
        enemy.get(),
        camera.get()
    };

    for (auto obj : objects)
        obj->Initialize();

    AudioManager::GetInstance().PlayBGM(BGMType::Stage1);
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