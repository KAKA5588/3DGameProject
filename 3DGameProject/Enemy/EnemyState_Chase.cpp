#include "EnemyState_Chase.h"
#include "EnemyState_Search.h"

EnemyState_Chase* EnemyState_Chase::Instance()
{
    static EnemyState_Chase instance;
    return &instance;
}

void EnemyState_Chase::Enter(EnemyBlackboard& bb)
{
    bb.lostTimer = 0.0f;
}

void EnemyState_Chase::Update(EnemyBlackboard& bb, float dt)
{
    Vec3 toPlayer = bb.playerPos - bb.pos;
    toPlayer.y = 0.0f;

    if (toPlayer.LengthSq() > 0.001f)
    {
        Vec3 dir = toPlayer.Normalized();
        bb.forward = dir;
        bb.velocity = dir * bb.moveSpeed * 1.5f;
    }

    if (!bb.canSeePlayer)
        bb.lostTimer += dt;
    else
        bb.lostTimer = 0.0f;
}

EnemyStateBase* EnemyState_Chase::CheckTransition(EnemyBlackboard& bb)
{
    if (bb.lostTimer > bb.lostTimeLimit)
        return EnemyState_Search::Instance();

    return nullptr;
}