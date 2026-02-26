#pragma once
#include "../Enemy/AI/EnemyStateBase.h"

class EnemyState_Idle : public EnemyStateBase
{
public:
    static EnemyState_Idle* Instance()
    {
        static EnemyState_Idle instance;
        return &instance;
    }

    void Enter(EnemyBlackboard& bb) override
    {
        bb.timer = 0.0f;
        bb.velocity = VGet(0, 0, 0);
    }

    void Update(EnemyBlackboard& bb, float dt) override
    {
        bb.timer += dt;
    }

    EnemyStateBase* CheckTransition(EnemyBlackboard& bb) override;
};