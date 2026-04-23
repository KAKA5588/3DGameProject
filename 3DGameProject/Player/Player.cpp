#include "Player.h"
#include "PlayerController.h"
#include "PlayerPhysics.h"
#include "../Stage/Stage.h"
#include "../Camera/Camera.h"
#include "../Actor/Actor.h"
#include "../AudioManager/AudioManager.h"
#include "DxLib.h"

Player::Player()
{
    velocity = { 0,0,0 };
}

Player::~Player()
{
    if (modelHandle != -1)
    {
        MV1DeleteModel(modelHandle);
        modelHandle = -1;
    }
}

void Player::SetStage(Stage* s)
{
    stage = s;
}

void Player::SetCamera(Camera* cam)
{
    camera = cam;
}

void Player::Initialize()
{
    modelHandle = MV1LoadModel("Resource/Player/Player.pmd");
    if (modelHandle == -1)
    {
        printfDx("Player model load failed\n");
        return;
    }

    position = { -116.0f, 1018.0f, -240.0f };
    MV1SetScale(modelHandle, VGet(12, 12, 12));

    controller = std::make_unique<PlayerController>();
    physics = std::make_unique<PlayerPhysics>();
}

void Player::Update(float dt)
{
    controller->Update(*this, camera, dt);
    physics->Update(*this, stage, dt);

    // ----- 足音処理（ループ制御）-----
    float speed = VSize(velocity);
    bool isMoving = (isGrounded && speed > 1.0f);

    if (isMoving)
    {
        if (!isFootStepPlaying)
        {
            AudioManager::GetInstance().PlaySE(SEType::FootStep);
            isFootStepPlaying = true;
        }
    }
    else
    {
        if (isFootStepPlaying)
        {
            AudioManager::GetInstance().StopSE(SEType::FootStep);
            isFootStepPlaying = false;
        }
    }

    MV1SetPosition(modelHandle, position);
}

void Player::Draw()
{
    ////敵が追っている中心点
    //DrawSphere3D(position, 20.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

    //if (modelHandle != -1)
    //{
    //    MV1DrawModel(modelHandle);
    //}
}
