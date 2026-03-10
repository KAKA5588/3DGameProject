#include "EnemyPhysics.h"
#include "Enemy.h"
#include "../Stage/Stage.h"
#include "DxLib.h"
#include <cmath>

static VECTOR ToVECTOR(const Vec3& v)
{
    return VGet(v.x, v.y, v.z);
}

void EnemyPhysics::Update(Enemy& enemy, Stage* stage, float dt)
{
    ApplyGravity(enemy, dt);

    Vec3 move = enemy.velocity * dt;
    Vec3 nextPos = enemy.position + move;

    // 横方向の衝突解決
    ResolveWall(enemy, stage, nextPos);

    // 床衝突解決
    ResolveFloor(enemy, stage, nextPos);

    enemy.position = nextPos;
}

void EnemyPhysics::ApplyGravity(Enemy& enemy, float dt)
{
    if (!enemy.isGrounded)
    {
        enemy.velocity.y += GRAVITY * dt;
    }
}

void EnemyPhysics::ResolveWall(Enemy& enemy, Stage* stage, Vec3& nextPos)
{
    if (!stage) return;

    float checkDist = radius + wallCheckOffset;
    VECTOR center = ToVECTOR(nextPos);

    // 4方向レイ
    VECTOR directions[4] =
    {
        VGet(1, 0, 0),
        VGet(-1, 0, 0),
        VGet(0, 0, 1),
        VGet(0, 0,-1)
    };

    for (int i = 0; i < 4; i++)
    {
        VECTOR end = VAdd(center, VScale(directions[i], checkDist));

        auto hit = MV1CollCheck_Line(
            stage->GetModelHandle(),
            -1,
            center,
            end
        );

        // ヒット判定
        if (hit.HitPosition.x > -100000.0f)
        {
            float dx = hit.HitPosition.x - nextPos.x;
            float dz = hit.HitPosition.z - nextPos.z;
            float dist = sqrtf(dx * dx + dz * dz);

            if (dist < radius)
            {
                float pushBack = radius - dist;

                nextPos.x -= directions[i].x * pushBack;
                nextPos.z -= directions[i].z * pushBack;

                // 壁方向の速度だけ止める
                if (directions[i].x != 0)
                    enemy.velocity.x = 0.0f;

                if (directions[i].z != 0)
                    enemy.velocity.z = 0.0f;
            }
        }
    }
}

void EnemyPhysics::ResolveFloor(Enemy& enemy, Stage* stage, Vec3& nextPos)
{
    enemy.isGrounded = false;

    if (!stage) return;

    VECTOR start = VGet(
        nextPos.x,
        nextPos.y,
        nextPos.z
    );

    VECTOR end = VGet(
        nextPos.x,
        nextPos.y - radius - 10.0f,
        nextPos.z
    );

    auto hit = MV1CollCheck_Line(
        stage->GetModelHandle(),
        -1,
        start,
        end
    );

    if (hit.HitPosition.y > -100000.0f)
    {
        float dist = nextPos.y - hit.HitPosition.y;

        if (dist >= 0.0f && dist <= radius + 5.0f)
        {
            nextPos.y = hit.HitPosition.y + radius;
            enemy.velocity.y = 0.0f;
            enemy.isGrounded = true;
        }
    }
}