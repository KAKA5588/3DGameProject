#pragma once
#include "EnemyState.h"

class Enemy;

class EnemyStateMachine
{
public:
    void ChangeState(Enemy* enemy, EnemyState* newState)
    {
        if (currentState)
        {
            currentState->Terminate(enemy);
        }

        currentState = newState;

        if (currentState)
        {
            currentState->Initialize(enemy);
        }
    }

    void Update(Enemy* enemy, float dt)
    {
        if (currentState)
        {
            currentState->Update(enemy, dt);
        }
    }

private:
    EnemyState* currentState = nullptr;
};
