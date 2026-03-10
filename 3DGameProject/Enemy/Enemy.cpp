#include "Enemy.h"
#include "EnemyState_Idle.h"

Enemy::Enemy()
{
    position = Vec3(1802.0f, 1141.0f, 2375.0f);
}

Enemy::~Enemy()
{
    if (enemyHandle != -1)
    {
        MV1DeleteModel(enemyHandle);
        enemyHandle = -1;
    }
}

#include "EnemyState_Search.h"

void Enemy::Initialize()
{
    blackboard.pos = position;

    enemyHandle = MV1LoadModel("Resource/Enemy/golem.mv1");

    ai.Initialize(EnemyState_Search::Instance(), blackboard);
}

void Enemy::Update(float dt)
{
    // ===== AI処理 =====

    Vec3 diff = blackboard.playerPos - blackboard.pos;
    float dist = diff.Length();

    blackboard.canSeePlayer = false;

    if (dist < blackboard.viewRange)
    {
        Vec3 forward = blackboard.forward;
        Vec3 dir = diff.Normalized();

        float dot =
            forward.x * dir.x +
            forward.y * dir.y +
            forward.z * dir.z;

        float angle = acosf(dot) * 180.0f / DX_PI_F;

        if (angle < blackboard.viewAngle * 0.5f)
        {
            blackboard.canSeePlayer = true;
        }
    }

    blackboard.canHearPlayer = false;

    if (blackboard.playerMadeSound &&
        dist < blackboard.hearRange)
    {
        blackboard.canHearPlayer = true;
        blackboard.lastHeardPos = blackboard.playerPos;
    }

    // AI更新
    ai.Update(blackboard, dt);

    // ★ 移動反映
    blackboard.pos += blackboard.velocity * dt;

    // 物理へ
    position = blackboard.pos;
    physics.Update(*this, stage, dt);

    // 物理結果を戻す
    blackboard.pos = position;

    // モデルへ反映
    MV1SetPosition(
        enemyHandle,
        VGet(position.x, position.y, position.z)
    );
    // ===== モデル回転 =====
    float yaw = atan2f(blackboard.forward.x, blackboard.forward.z);
    yaw += DX_PI_F;
    // Y軸回転をセット
    MV1SetRotationXYZ(
        enemyHandle,
        VGet(0.0f, yaw, 0.0f)
    );
}

void Enemy::Draw()
{
    MV1DrawModel(enemyHandle);
}