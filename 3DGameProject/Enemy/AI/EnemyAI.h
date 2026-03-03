#pragma once
#include "EnemyStateBase.h"
#include "EnemyBlackboard.h"

class EnemyAI
{
public:
    void Initialize(EnemyStateBase* startState, EnemyBlackboard& bb);
    void Update(EnemyBlackboard& bb, float dt);

private:
    EnemyStateBase* currentState = nullptr;
};