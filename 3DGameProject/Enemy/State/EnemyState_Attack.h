#pragma once
#include "../AI/EnemyStateBase.h"

class EnemyState_Attack : public EnemyStateBase
{
public:
    static EnemyState_Attack* Instance();

    void Enter(EnemyBlackboard& bb) override;
    void Update(EnemyBlackboard& bb, float dt) override;
    EnemyStateBase* CheckTransition(EnemyBlackboard& bb) override;
};