#pragma once
#include "DxLib.h"
#include "../Actor/Actor.h"
#include "../GameObject/GameObject.h"

class Stage;

class Camera : public GameObject
{
public:
    Camera();

    void Initialize() override;
    void Update(float dt) override;
    void Apply();

    void SetTarget(Actor* target);
    void SetStage(Stage* stage);

    float GetYaw() const { return yaw; }

private:
    Actor* target = nullptr;
    Stage* stage = nullptr;

    // 回転
    float yaw;
    float pitch;

    // ===== 調整用（ヘッダーで触る）=====
    float distance;        // プレイヤーとの距離（固定）
    float targetHeight;    // 注視点の高さ

    float mouseSensitivity;

    float pitchMin;
    float pitchMax;
    // ====================================

    VECTOR position;

    float smoothDistance;
    float rayOffset; // カメラの太さ
};

