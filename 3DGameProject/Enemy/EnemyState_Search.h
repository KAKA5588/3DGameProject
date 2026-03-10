#pragma once
#include "../Enemy/AI/EnemyStateBase.h"

class EnemyState_Search : public EnemyStateBase
{
public:
    static EnemyState_Search* Instance();

    void Enter(EnemyBlackboard& bb) override;
    void Update(EnemyBlackboard& bb, float dt) override;
    EnemyStateBase* CheckTransition(EnemyBlackboard& bb) override;
};