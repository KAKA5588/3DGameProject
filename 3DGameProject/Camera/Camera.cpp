#include "Camera.h"
#include "../MouseInput/MouseInput.h"
#include <cmath>

Camera::Camera()
{
    yaw = 0.0f;
    pitch = 0.0f;

    // ===== カメラ調整 =====
    distance = 360.0f; // ← 近い / 遠い はここだけ
    targetHeight = 180.0f;  // 頭あたりを見る
    mouseSensitivity = 0.002f;

    pitchMin = -DX_PI_F / 3.0f;
    pitchMax = DX_PI_F / 3.0f;
    // ======================
}

void Camera::SetTarget(Actor* actor)
{
    target = actor;
}

void Camera::Initialize()
{
    SetMouseDispFlag(FALSE);
}

void Camera::Update(float dt)
{
    if (!target) return;

    MouseInput::Update();

    // マウス操作（回転のみ）
    yaw += MouseInput::GetDeltaX() * mouseSensitivity;
    pitch -= MouseInput::GetDeltaY() * mouseSensitivity;

    if (pitch < pitchMin) pitch = pitchMin;
    if (pitch > pitchMax) pitch = pitchMax;

    VECTOR targetPos = VGet(
        target->position.x,
        target->position.y + targetHeight,
        target->position.z
    );

    // 距離固定の球面座標
    position.x = targetPos.x - distance * cosf(pitch) * sinf(yaw);
    position.y = targetPos.y - distance * sinf(pitch);
    position.z = targetPos.z - distance * cosf(pitch) * cosf(yaw);
}

void Camera::Apply()
{
    if (!target) return;

    VECTOR targetPos = VGet(
        target->position.x,
        target->position.y + targetHeight,
        target->position.z
    );

    SetCameraPositionAndTarget_UpVecY(position, targetPos);
}
