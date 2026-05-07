#include "EnemyState_Attack.h"
#include "EnemyState_Chase.h"

EnemyState_Attack* EnemyState_Attack::Instance()
{
    static EnemyState_Attack instance;
    return &instance;
}

void EnemyState_Attack::Enter(EnemyBlackboard& bb)
{
    bb.velocity = { 0,0,0 };
    bb.timer = 0.0f;

    // ó‘ÔƒZƒbƒg
    bb.state = EnemyStateType::Attack;
}

void EnemyState_Attack::Update(EnemyBlackboard& bb, float dt)
{
    bb.timer += dt;

    Vec3 toPlayer = bb.playerPos - bb.pos;
    toPlayer.y = 0.0f;

    if (toPlayer.LengthSq() > 0.001f)
    {
        bb.forward = toPlayer.Normalized();
    }
}

EnemyStateBase* EnemyState_Attack::CheckTransition(EnemyBlackboard& bb)
{
    // 1.5•bŒã‚É’ÇÕ‚Ö–ß‚é
    if (bb.timer > 1.5f)
    {
        return EnemyState_Chase::Instance();
    }

    return nullptr;
}