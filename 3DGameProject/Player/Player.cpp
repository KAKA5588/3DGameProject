#include "Player.h"
#include "PlayerController.h"
#include "PlayerPhysics.h"
#include "../Stage/Stage.h"
#include "../Camera/Camera.h"
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
    controller->Update(*this, camera);
    physics->Update(*this, stage, dt);

    MV1SetPosition(
        modelHandle,
        VGet(position.x, position.y, position.z)
    );
}

void Player::Draw()
{
    if (modelHandle != -1)
    {
        MV1DrawModel(modelHandle);
    }
}
