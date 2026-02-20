#include "Enemy.h"
#include "EnemyState_Idle.h"

Enemy::Enemy()
{
    position = VGet(235.0f, 323.0f, 8436.0f);
}

void Enemy::Initialize()
{
    static EnemyState_Idle idleState;
    stateMachine.ChangeState(this, &idleState);
}

void Enemy::Update(float dt)
{
    stateMachine.Update(this, dt);
}

void Enemy::Draw()
{
    VECTOR minPos = VGet(
        position.x - size.x * 0.5f,
        position.y,
        position.z - size.z * 0.5f
    );

    VECTOR maxPos = VGet(
        position.x + size.x * 0.5f,
        position.y + size.y,
        position.z + size.z * 0.5f
    );

    DrawCube3D(
        minPos,
        maxPos,
        GetColor(255, 0, 0),
        GetColor(0, 0, 0),
        TRUE
    );
}
