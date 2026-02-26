#include "EnemyState_Chase.h"
#include "EnemyState_Idle.h"

EnemyStateBase* EnemyState_Chase::CheckTransition(EnemyBlackboard& bb)
{
    // Œ©Ž¸‚Á‚½‚çIdle‚Ö–ß‚é
    if (!bb.canSeePlayer)
    {
        return EnemyState_Idle::Instance();
    }

    return this;
}