#include "Enemy.h"
#include "EnemyState_Idle.h"

Enemy::Enemy()
{
    position = VGet(235.0f, 323.0f, 8436.0f);
}

void Enemy::Initialize()
{
    blackboard.pos = position;
    ai.Initialize(EnemyState_Idle::Instance(), blackboard);
}

void Enemy::Update(float dt)
{
    // プレイヤーとの距離
    VECTOR diff = VSub(playerPos, blackboard.pos);
    float dist = VSize(diff);

    blackboard.playerPos = playerPos;

    // 視覚判定
    blackboard.canSeePlayer = false;

    if (dist < blackboard.viewRange)
    {
        VECTOR forward = VGet(0, 0, 1); // 今は仮で前向き固定
        VECTOR dir = VNorm(diff);

        float dot = VDot(forward, dir);
        float angle = acosf(dot) * 180.0f / DX_PI_F;

        if (angle < blackboard.viewAngle * 0.5f)
        {
            blackboard.canSeePlayer = true;
        }
    }

    
    // 聴覚判定
    blackboard.canHearPlayer = false;

    if (blackboard.playerMadeSound &&
        dist < blackboard.hearRange)
    {
        blackboard.canHearPlayer = true;
        blackboard.lastHeardPos = playerPos;
    }

    // AI更新
    ai.Update(blackboard, dt);

    position = blackboard.pos;
}

void Enemy::Draw()
{
    VECTOR minPos = VGet(
        position.x - size.x * 0.5f,
        position.y,
        position.z - size.z * 0.5f
    );

    VECTOR maxPos = VGet(
        position.x + size.x * 0.5f,
        position.y + size.y,
        position.z + size.z * 0.5f
    );

    DrawCube3D(minPos, maxPos,
        GetColor(255, 0, 0),
        GetColor(0, 0, 0),
        TRUE);
}