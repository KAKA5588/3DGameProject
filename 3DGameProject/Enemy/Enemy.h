#pragma once
#include "DxLib.h"
#include "../Actor/Actor.h"
#include "EnemyStateMachine.h"
#include "../GameObject/GameObject.h"
#include "../Enemy/AI/EnemyAI.h"
#include "../Enemy/AI/EnemyBlackboard.h"

class Enemy : public Actor
{
public:
    Enemy();

    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

    void SetPlayerPos(VECTOR pos) { playerPos = pos; }

private:
    VECTOR position{};
    VECTOR size{ 30.0f, 80.0f, 30.0f };

    VECTOR playerPos{};

    EnemyBlackboard blackboard;
    EnemyAI ai;
};