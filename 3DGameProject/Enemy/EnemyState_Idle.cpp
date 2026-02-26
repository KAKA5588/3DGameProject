#include "EnemyState_Idle.h"
#include "EnemyState_Chase.h"

EnemyStateBase* EnemyState_Idle::CheckTransition(EnemyBlackboard& bb)
{
    // Œ©‚¦‚½‚ç’ÇÕŠJn
    if (bb.canSeePlayer)
    {
        return EnemyState_Chase::Instance();
    }

    return this;
}