#pragma once
#include "../Enemy/AI/EnemyStateBase.h"

class EnemyState_Idle : public EnemyStateBase
{
public:
    static EnemyState_Idle* Instance();

    void Enter(EnemyBlackboard& bb) override;
    void Update(EnemyBlackboard& bb, float dt) override;
    EnemyStateBase* CheckTransition(EnemyBlackboard& bb) override;
};