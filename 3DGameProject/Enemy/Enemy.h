#pragma once
#include "DxLib.h"
#include "../Actor/Actor.h"
#include "EnemyStateMachine.h"
#include "../GameObject/GameObject.h"

class Enemy : public Actor
{
public:
    Enemy();
    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

    VECTOR GetPosition() const { return position; }

private:
    VECTOR position{};
    VECTOR size{ 30.0f, 80.0f, 30.0f };

    EnemyStateMachine stateMachine;
};
