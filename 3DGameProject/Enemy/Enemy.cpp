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

void Enemy::Initialize()
{
    blackboard.pos = position;

    enemyHandle = MV1LoadModel("Resource/Enemy/golem.mv1");

    ai.Initialize(EnemyState_Idle::Instance(), blackboard);
}

void Enemy::Update(float dt)
{
    // ===== AI処理 =====

    Vec3 diff = blackboard.playerPos - blackboard.pos;
    float dist = diff.Length();

    blackboard.canSeePlayer = false;

    if (dist < blackboard.viewRange)
    {
        Vec3 forward = Vec3(0, 0, 1);
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

    ai.Update(blackboard, dt);

    // ===== AI結果を物理へ渡す =====
    position = blackboard.pos;

    // 物理更新（重力・床判定）
    physics.Update(*this, stage, dt);

    // 物理結果をblackboardへ戻す
    blackboard.pos = position;

    // モデルへ反映
    MV1SetPosition(
        enemyHandle,
        VGet(position.x, position.y, position.z)
    );
}

void Enemy::Draw()
{
    MV1DrawModel(enemyHandle);
}