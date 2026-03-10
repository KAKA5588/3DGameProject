#pragma once
#include "../Vec3/Vec3.h"

class Enemy;
class Stage;

class EnemyPhysics
{
public:
    void Update(Enemy& enemy, Stage* stage, float dt);

private:
    const float GRAVITY = -40.0f;
    const float radius = 15.0f;
    const float wallCheckOffset = 5.0f;

    void ApplyGravity(Enemy& enemy, float dt);
    void ResolveWall(Enemy& enemy, Stage* stage, Vec3& nextPos);
    void ResolveFloor(Enemy& enemy, Stage* stage, Vec3& nextPos);
};