#pragma once
#include "../Enemy/AI/EnemyStateBase.h"

class EnemyState_Chase : public EnemyStateBase
{
public:
    static EnemyState_Chase* Instance();

    void Enter(EnemyBlackboard& bb) override;
    void Update(EnemyBlackboard& bb, float dt) override;
    EnemyStateBase* CheckTransition(EnemyBlackboard& bb) override;
};