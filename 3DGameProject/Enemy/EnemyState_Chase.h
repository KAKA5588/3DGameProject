#pragma once
#include "../Enemy/AI/EnemyStateBase.h"

class EnemyState_Chase : public EnemyStateBase
{
public:
    static EnemyState_Chase* Instance()
    {
        static EnemyState_Chase instance;
        return &instance;
    }

    void Enter(EnemyBlackboard& bb) override
    {
    }

    void Update(EnemyBlackboard& bb, float dt) override
    {
        // playerPos ‚ðŽg‚¤
        VECTOR dir = VSub(bb.playerPos, bb.pos);
        dir = VNorm(dir);

        bb.velocity = VScale(dir, bb.moveSpeed);
        bb.pos = VAdd(bb.pos, VScale(bb.velocity, dt));
    }

    EnemyStateBase* CheckTransition(EnemyBlackboard& bb) override;
};