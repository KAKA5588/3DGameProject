#pragma once
#include "DxLib.h"
#include "../Actor/Actor.h"
#include "EnemyPhysics.h"
#include "../Enemy/AI/EnemyAI.h"
#include "../Enemy/AI/EnemyBlackboard.h"

class Stage;

class Enemy : public Actor
{
public:
    Enemy();
    ~Enemy();

    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

    void SetPlayerPos(const Vec3& pos) { blackboard.playerPos = pos; }
    void SetStage(Stage* s) { stage = s; }

   // ï®óùóp
    Vec3 velocity{ 0,0,0 };
    bool isGrounded = false;

private:
    Vec3 size{ 30.0f, 80.0f, 30.0f };

    Stage* stage = nullptr;

    EnemyBlackboard blackboard;
    EnemyAI ai;
    EnemyPhysics physics;

    int enemyHandle = -1;
};