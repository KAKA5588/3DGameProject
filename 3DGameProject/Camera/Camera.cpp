#include "Camera.h"
#include "../MouseInput/MouseInput.h"
#include "../Stage/Stage.h"
#include <cmath>

Camera::Camera()
{
    yaw = 0.0f;
    pitch = 0.0f;

    distance = 0.0f;          
    targetHeight = 180.0f;    // 目の高さ
    mouseSensitivity = 0.002f;

    pitchMin = -DX_PI_F / 3.0f;
    pitchMax = DX_PI_F / 3.0f;

    flashHandle = -1;
}

void Camera::SetTarget(Actor* actor)
{
    target = actor;
}

void Camera::Initialize()
{
    SetMouseDispFlag(FALSE);

    flashHandle = MV1LoadModel("Resource/Flash/Flash.mv1");

    if (flashHandle == -1)
    {
        printfDx("Flash model load failed\n");
    }

    // 30倍スケール
    MV1SetScale(flashHandle, VGet(4.0f, 4.0f, 4.0f));
}

void Camera::Update(float dt)
{
    if (!target) return;

    MouseInput::Update();

    yaw += MouseInput::GetDeltaX() * mouseSensitivity;
    pitch -= MouseInput::GetDeltaY() * mouseSensitivity;

    if (pitch < pitchMin) pitch = pitchMin;
    if (pitch > pitchMax) pitch = pitchMax;

    // ===== 一人称カメラ位置 =====
    VECTOR targetPos = VGet(
        target->position.x,
        target->position.y + targetHeight,
        target->position.z
    );

    position = targetPos;

    // ===== カメラ前方向 =====
    VECTOR forward = VGet(
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    );

    VECTOR right = VNorm(VCross(forward, VGet(0, 1, 0)));
    VECTOR up = VGet(0, 1, 0);

    // ===== 右下オフセット =====
    VECTOR flashPos = VAdd(position,
        VAdd(
            VScale(forward, 40.0f),   // 前
            VAdd(
                VScale(right, 20.0f), // 右
                VScale(up, -20.0f)    // 下
            )
        )
    );

    MV1SetPosition(flashHandle, flashPos);

    // モデル向き調整（必要なら +DX_PI_F 消してください）
    MV1SetRotationXYZ(flashHandle, VGet(pitch, yaw + DX_PI_F, 0));
}

void Camera::Apply()
{
    if (!target) return;

    VECTOR forward = VGet(
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    );

    VECTOR cameraTarget = VAdd(position, forward);

    SetCameraPositionAndTarget_UpVecY(position, cameraTarget);

    SetCameraNearFar(1.0f, 10000.0f);
}

void Camera::Draw()
{
    if (flashHandle == -1) return;

    // カメラ前方向
    VECTOR forward = VGet(
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    );

    // 右ベクトルを再計算（超重要）
    VECTOR right = VNorm(VCross(forward, VGet(0, 1, 0)));

    // 上ベクトルを再計算（安定用）
    VECTOR up = VNorm(VCross(right, forward));

    // ===== 右下固定オフセット =====
    VECTOR drawPos = VAdd(position,
        VAdd(
            VScale(forward, 100.0f),  // 前に出す
            VAdd(
                VScale(right, -60.0f),  // 右
                VScale(up, -30.0f)     // 下
            )
        )
    );

    MV1SetPosition(flashHandle, drawPos);
    MV1SetRotationXYZ(
        flashHandle,
        VGet(pitch, yaw - DX_PI_F / 2.0f, 0)
    );

    // 武器はZ無効
    SetUseZBuffer3D(FALSE);
    SetWriteZBuffer3D(FALSE);

    MV1DrawModel(flashHandle);

    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
}

void Camera::SetStage(Stage* s)
{
    stage = s;
}