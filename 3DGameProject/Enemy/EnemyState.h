#pragma once

class Enemy;

class EnemyState
{
public:
    virtual ~EnemyState() {}

    virtual void Initialize(Enemy* enemy) {}
    virtual void Update(Enemy* enemy, float dt) {}
    virtual void Terminate(Enemy* enemy) {}
};
