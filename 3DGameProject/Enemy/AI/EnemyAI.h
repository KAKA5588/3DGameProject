#pragma once
#include "EnemyStateBase.h"

class EnemyAI
{
public:
    void Initialize(EnemyStateBase* startState, EnemyBlackboard& bb)
    {
        currentState = startState;
        currentState->Enter(bb);
    }

    void Update(EnemyBlackboard& bb, float dt)
    {
        currentState->Update(bb, dt);

        EnemyStateBase* next = currentState->CheckTransition(bb);

        if (next != currentState)
        {
            currentState = next;
            currentState->Enter(bb);
        }
    }

private:
    EnemyStateBase* currentState = nullptr;
};