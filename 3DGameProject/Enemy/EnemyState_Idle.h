#pragma once
#include "EnemyState.h"

class EnemyState_Idle : public EnemyState
{
public:
    void Initialize(Enemy* enemy) override;
    void Update(Enemy* enemy, float dt) override;
    void Terminate(Enemy* enemy) override;
};
