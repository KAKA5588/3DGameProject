#include "Camera.h"
#include "../MouseInput/MouseInput.h"
#include <cmath>

Camera::Camera()
{
    yaw = 0.0f;
    pitch = 0.0f;

    targetHeight = 180.0f;
    mouseSensitivity = 0.002f;

    pitchMin = -DX_PI_F / 3.0f;
    pitchMax = DX_PI_F / 3.0f;
}

void Camera::SetTarget(Actor* actor)
{
    target = actor;
}
void Camera::Initialize()
{
    SetMouseDispFlag(FALSE);

    DeleteLightHandle(0);

    // 少しだけ環境光アップ（真っ暗すぎ防止）
    COLOR_F ambient;
    ambient.r = 0.01f;
    ambient.g = 0.01f;
    ambient.b = 0.01f;
    ambient.a = 1.0f;

    SetGlobalAmbientLight(ambient);
    SetUseLighting(TRUE);

    flashHandle = MV1LoadModel("Resource/Flash/Flash.mv1");
    MV1SetScale(flashHandle, VGet(4.0f, 4.0f, 4.0f));

    // 広くて強いスポットライト
    lightHandle = CreateSpotLightHandle(
        VGet(0, 0, 0),
        VGet(0, 0, 1),
        DX_PI_F / 6.0f,     // ★ 内角かなり広い
        DX_PI_F / 3.0f,     // ★ 外角さらに広い
        3000.0f,            // ★ 固定距離（安定）
        15.0f,              // ★ 明るさかなり強い
        0.000001f,          // ★ 減衰かなり弱い
        0.0f
    );

    SetLightEnableHandle(lightHandle, TRUE);

    // 近距離用ポイントライト強化
    pointLightHandle = CreatePointLightHandle(
        VGet(0, 0, 0),
        500.0f,     // 有効距離アップ
        4.0f,       // 明るさアップ
        0.0005f,    // 減衰弱め
        0.0f
    );

    SetLightEnableHandle(pointLightHandle, TRUE);
}
void Camera::Update(float dt)
{
    if (!target) return;

    MouseInput::Update();

    yaw += MouseInput::GetDeltaX() * mouseSensitivity;
    pitch -= MouseInput::GetDeltaY() * mouseSensitivity;

    if (pitch < pitchMin) pitch = pitchMin;
    if (pitch > pitchMax) pitch = pitchMax;

    position = VGet(
        target->position.x,
        target->position.y + targetHeight,
        target->position.z
    );

    VECTOR forward = VGet(
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    );

    VECTOR right = VNorm(VCross(forward, VGet(0, 1, 0)));
    VECTOR up = VNorm(VCross(right, forward));

    VECTOR drawPos = VAdd(position,
        VAdd(
            VScale(forward, 100.0f),
            VAdd(
                VScale(right, -60.0f),
                VScale(up, -30.0f)
            )
        )
    );

    // モデル更新
    MV1SetPosition(flashHandle, drawPos);
    MV1SetRotationXYZ(flashHandle, VGet(pitch, yaw - DX_PI_F / 2.0f, 0));

    // ライト更新
    SetLightPositionHandle(lightHandle, drawPos);
    SetLightDirectionHandle(lightHandle, forward);

    // ★ 近距離ポイントライトをカメラ位置に
    SetLightPositionHandle(pointLightHandle, position);
}

//void Camera::Initialize()
//{
//    SetMouseDispFlag(FALSE);
//
//    // 追加：フリーカメラ初期位置
//    freePosition = VGet(0, 300, -500);
//
//    DeleteLightHandle(0);
//}

//void Camera::Update(float dt)
//{
//    MouseInput::Update();
//
//    // ===== Fキーでモード切替 =====
//    if (CheckHitKey(KEY_INPUT_F) == 1)
//    {
//        isFreeCamera = !isFreeCamera;
//
//        // フリーに入る瞬間、現在位置をコピー
//        if (isFreeCamera)
//        {
//            freePosition = position;
//        }
//    }
//
//    // =============================
//
//    // マウス回転（共通）
//    yaw += MouseInput::GetDeltaX() * mouseSensitivity;
//    pitch -= MouseInput::GetDeltaY() * mouseSensitivity;
//
//    if (pitch < pitchMin) pitch = pitchMin;
//    if (pitch > pitchMax) pitch = pitchMax;
//
//    VECTOR forward = VGet(
//        cosf(pitch) * sinf(yaw),
//        sinf(pitch),
//        cosf(pitch) * cosf(yaw)
//    );
//
//    VECTOR right = VNorm(VCross(forward, VGet(0, 1, 0)));
//
//    // =============================
//    //  フリーカメラ
//    // =============================
//    if (isFreeCamera)
//    {
//        if (CheckHitKey(KEY_INPUT_W)) freePosition = VAdd(freePosition, VScale(forward, freeSpeed * dt));
//        if (CheckHitKey(KEY_INPUT_S)) freePosition = VAdd(freePosition, VScale(forward, -freeSpeed * dt));
//        if (CheckHitKey(KEY_INPUT_D)) freePosition = VAdd(freePosition, VScale(right, freeSpeed * dt));
//        if (CheckHitKey(KEY_INPUT_A)) freePosition = VAdd(freePosition, VScale(right, -freeSpeed * dt));
//        if (CheckHitKey(KEY_INPUT_SPACE)) freePosition.y += freeSpeed * dt;
//        if (CheckHitKey(KEY_INPUT_LSHIFT)) freePosition.y -= freeSpeed * dt;
//
//        position = freePosition;
//    }
//    // =============================
//    //  通常カメラ（今まで通り）
//    // =============================
//    else
//    {
//        if (!target) return;
//
//        position = VGet(
//            target->position.x,
//            target->position.y + targetHeight,
//            target->position.z
//        );
//    }
//
//    // ===== ライト更新（共通）=====
//    SetLightPositionHandle(lightHandle, position);
//    SetLightDirectionHandle(lightHandle, forward);
//    SetLightPositionHandle(pointLightHandle, position);
//}

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

    SetUseZBuffer3D(FALSE);
    SetWriteZBuffer3D(FALSE);

    MV1DrawModel(flashHandle);

    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
}

//void Camera::Draw()
//{
//    if (flashHandle != -1)
//    {
//        SetUseZBuffer3D(FALSE);
//        SetWriteZBuffer3D(FALSE);
//
//        MV1DrawModel(flashHandle);
//
//        SetUseZBuffer3D(TRUE);
//        SetWriteZBuffer3D(TRUE);
//    }
//
//    // =========================
//    // デバッグ座標表示
//    // =========================
//    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
//
//    DrawFormatString(
//        20, 20,
//        GetColor(0, 255, 0),
//        "Camera Pos : X=%.2f  Y=%.2f  Z=%.2f",
//        position.x,
//        position.y,
//        position.z
//    );
//
//    DrawFormatString(
//        20, 45,
//        GetColor(0, 200, 255),
//        "Yaw=%.2f  Pitch=%.2f",
//        yaw,
//        pitch
//    );
//
//    DrawFormatString(
//        20, 70,
//        GetColor(255, 200, 0),
//        "Mode : %s",
//        isFreeCamera ? "FREE CAMERA" : "PLAYER CAMERA"
//    );
//
//    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//}

void Camera::SetStage(Stage* s)
{
    stage = s;
}