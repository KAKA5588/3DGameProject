#include "Camera.h"
#include "../MouseInput/MouseInput.h"
#include "../Stage/Stage.h"
#include <cmath>

Camera::Camera()
{
    yaw = 0.0f;
    pitch = 0.0f;

    distance = 360.0f;
    targetHeight = 180.0f;
    mouseSensitivity = 0.002f;
    float rayOffset = 20.0f; // カメラの太さ

    pitchMin = -DX_PI_F / 3.0f;
    pitchMax = DX_PI_F / 3.0f;

    smoothDistance = distance;   
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

    yaw += MouseInput::GetDeltaX() * mouseSensitivity;
    pitch -= MouseInput::GetDeltaY() * mouseSensitivity;

    if (pitch < pitchMin) pitch = pitchMin;
    if (pitch > pitchMax) pitch = pitchMax;

    VECTOR targetPos = VGet(
        target->position.x,
        target->position.y + targetHeight,
        target->position.z
    );

    float desiredDistance = distance;

    // 理想カメラ位置
    VECTOR idealPos = VGet(
        targetPos.x - distance * cosf(pitch) * sinf(yaw),
        targetPos.y - distance * sinf(pitch),
        targetPos.z - distance * cosf(pitch) * cosf(yaw)
    );

    // ===== 衝突判定 =====
   // ===== 衝突判定（4方向レイ）=====
    if (stage)
    {
        float nearestDistance = distance;

        // カメラの右ベクトルを計算
        VECTOR forward = VNorm(VSub(idealPos, targetPos));
        VECTOR right = VNorm(VCross(VGet(0, 1, 0), forward));
        VECTOR up = VGet(0, 1, 0);

        VECTOR offsets[4] =
        {
            VGet(0,0,0),                         // 中央
            VScale(right,  rayOffset),           // 右
            VScale(right, -rayOffset),           // 左
            VScale(up,     rayOffset)            // 上
        };

        for (int i = 0; i < 4; i++)
        {
            VECTOR start = VAdd(targetPos, offsets[i]);
            VECTOR end = VAdd(idealPos, offsets[i]);

            MV1_COLL_RESULT_POLY result =
                MV1CollCheck_Line(
                    stage->GetModelHandle(),
                    -1,
                    start,
                    end
                );

            if (result.HitFlag)
            {
                VECTOR hitVec = VSub(result.Position[0], start);
                float hitDistance = VSize(hitVec);

                float d = hitDistance - 15.0f;

                if (d < nearestDistance)
                    nearestDistance = d;
            }
        }

        if (nearestDistance < 80.0f)
            nearestDistance = 80.0f;

        desiredDistance = nearestDistance;
    }

    // ===== スムーズ制御 =====
    float approachSpeed = 0.15f; // 近づくとき速め
    float returnSpeed = 0.05f; // 戻るときゆっくり

    if (smoothDistance > desiredDistance)
        smoothDistance += (desiredDistance - smoothDistance) * approachSpeed;
    else
        smoothDistance += (desiredDistance - smoothDistance) * returnSpeed;

    // ===== 最終位置 =====
    position.x = targetPos.x - smoothDistance * cosf(pitch) * sinf(yaw);
    position.y = targetPos.y - smoothDistance * sinf(pitch);
    position.z = targetPos.z - smoothDistance * cosf(pitch) * cosf(yaw);
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

void Camera::SetStage(Stage* s)
{
    stage = s;
}