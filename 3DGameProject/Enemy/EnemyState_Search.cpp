#include "EnemyState_Search.h"
#include "EnemyState_Chase.h"
#include "DxLib.h"

EnemyState_Search* EnemyState_Search::Instance()
{
    static EnemyState_Search instance;
    return &instance;
}

void EnemyState_Search::Enter(EnemyBlackboard& bb)
{
    float angle = GetRand(360);
    float rad = angle * DX_PI_F / 180.0f;

    bb.forward = Vec3(cosf(rad), 0.0f, sinf(rad));
}

void EnemyState_Search::Update(EnemyBlackboard& bb, float dt)
{
    bb.velocity = bb.forward * bb.moveSpeed;
}

EnemyStateBase* EnemyState_Search::CheckTransition(EnemyBlackboard& bb)
{
    if (bb.canSeePlayer || bb.canHearPlayer)
    {
        return EnemyState_Chase::Instance();
    }

    return nullptr;
}