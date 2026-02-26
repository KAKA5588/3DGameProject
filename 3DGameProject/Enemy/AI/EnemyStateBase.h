#pragma once
#include "EnemyBlackboard.h"

class EnemyStateBase
{
public:
    virtual ~EnemyStateBase() {}

    virtual void Enter(EnemyBlackboard& bb) {}
    virtual void Update(EnemyBlackboard& bb, float dt) = 0;
    virtual EnemyStateBase* CheckTransition(EnemyBlackboard& bb) = 0;
};