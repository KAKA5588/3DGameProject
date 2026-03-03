#include "PlayerPhysics.h"
#include "Player.h"
#include "../Stage/Stage.h"
#include "DxLib.h"

constexpr float GRAVITY = -40.0f;
constexpr float WALL_CHECK_DIST = 6.0f;

static VECTOR ToVECTOR(const Vec3& v)
{
    return VGet(v.x, v.y, v.z);
}

void PlayerPhysics::Update(Player& player, Stage* stage, float dt)
{
    ApplyGravity(player, dt);

    Vec3 nextPos = player.position + player.velocity * dt;

    ResolveFloor(player, stage, nextPos);
    ResolveWall(player, stage, nextPos);

    player.position = nextPos;
}

void PlayerPhysics::ApplyGravity(Player& player, float dt)
{
    if (!player.isGrounded)
    {
        player.velocity.y += GRAVITY * dt;
    }
}

// 床判定（下向きレイ）
void PlayerPhysics::ResolveFloor(Player& player, Stage* stage, Vec3& nextPos)
{
    player.isGrounded = false;
    if (!stage) return;
    if (player.velocity.y > 0.0f) return;

    VECTOR start = ToVECTOR({
        nextPos.x,
        player.position.y,
        nextPos.z
        });

    VECTOR end = ToVECTOR({
        nextPos.x,
        nextPos.y - radius - 5.0f,
        nextPos.z
        });

    auto hit = MV1CollCheck_Line(
        stage->GetModelHandle(),
        -1,
        start,
        end
    );

    float dist = start.y - hit.HitPosition.y;

    if (hit.HitPosition.y > -100000.0f &&
        dist >= 0.0f &&
        dist <= 20.0f)
    {
        nextPos.y = hit.HitPosition.y + radius;
        player.velocity.y = 0.0f;
        player.isGrounded = true;
    }
}

// 壁判定（横方向4本）
void PlayerPhysics::ResolveWall(Player& player, Stage* stage, Vec3& nextPos)
{
    if (!stage) return;

    Vec3 move = nextPos - player.position;

    // 横方向のみ
    Vec3 horizontalMove{ move.x, 0.0f, move.z };
    float moveLength = horizontalMove.Length();
    if (moveLength < 0.0001f) return;

    Vec3 dir = horizontalMove.Normalized();

    float checkDist = moveLength + 2.0f;

    // 4方向オフセット（半径分）
    Vec3 offsets[4] =
    {
        {  radius, 0, 0 },
        { -radius, 0, 0 },
        { 0, 0,  radius },
        { 0, 0, -radius }
    };

    for (int i = 0; i < 4; ++i)
    {
        Vec3 startPos;
        startPos.x = player.position.x + offsets[i].x;
        startPos.y = player.position.y + radius;   // 腰の高さ
        startPos.z = player.position.z + offsets[i].z;

        Vec3 endPos = startPos + dir * checkDist;

        VECTOR start = VGet(startPos.x, startPos.y, startPos.z);
        VECTOR end = VGet(endPos.x, endPos.y, endPos.z);

        auto hit = MV1CollCheck_Line(
            stage->GetModelHandle(),
            -1,
            start,
            end
        );

        if (hit.HitPosition.y > -100000.0f)
        {
            float dx = hit.HitPosition.x - startPos.x;
            float dz = hit.HitPosition.z - startPos.z;
            float hitDist = sqrtf(dx * dx + dz * dz);

            float heightDiff = fabs(hit.HitPosition.y - startPos.y);

            if (hitDist <= checkDist && heightDiff < 10.0f)
            {
                // めり込み防止位置
                nextPos.x = player.position.x + dir.x * (hitDist - 0.5f);
                nextPos.z = player.position.z + dir.z * (hitDist - 0.5f);

                player.velocity.x = 0.0f;
                player.velocity.z = 0.0f;

                return; // 1本でも当たれば止める
            }
        }
    }
}