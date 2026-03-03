#include "EnemyState_Idle.h"
#include "EnemyState_Chase.h"

EnemyState_Idle* EnemyState_Idle::Instance()
{
    static EnemyState_Idle instance;
    return &instance;
}

void EnemyState_Idle::Enter(EnemyBlackboard& bb)
{
    bb.timer = 0.0f;
    bb.velocity = Vec3(0, 0, 0);   // © Vec3”Å
}

void EnemyState_Idle::Update(EnemyBlackboard& bb, float dt)
{
    bb.timer += dt;

    // Idle’†‚Íí‚É~‚ß‚éiˆÀ‘Sôj
    bb.velocity = Vec3(0, 0, 0);
}

EnemyStateBase* EnemyState_Idle::CheckTransition(EnemyBlackboard& bb)
{
    if (bb.canSeePlayer)
    {
        return EnemyState_Chase::Instance();
    }

    return nullptr;
}