#include "PlayerController.h"
#include "Player.h"
#include "../Camera/Camera.h"
#include "DxLib.h"
#include <cmath>

void PlayerController::Update(Player& player, Camera* camera, float dt)
{
    if (!camera) return;

    Vec3 input{ 0,0,0 };

    if (CheckHitKey(KEY_INPUT_W)) input.z += 1;
    if (CheckHitKey(KEY_INPUT_S)) input.z -= 1;
    if (CheckHitKey(KEY_INPUT_A)) input.x -= 1;
    if (CheckHitKey(KEY_INPUT_D)) input.x += 1;

    float yaw = camera->GetYaw();

    Vec3 forward{ sinf(yaw), 0.0f, cosf(yaw) };
    Vec3 right{ cosf(yaw), 0.0f, -sinf(yaw) };

    Vec3 dir{ 0,0,0 };

    if (input.x != 0 || input.z != 0)
    {
        dir = forward * input.z + right * input.x;

        float len = sqrtf(dir.x * dir.x + dir.z * dir.z);
        if (len > 0.0f)
        {
            dir.x /= len;
            dir.z /= len;
        }

        player.velocity.x = dir.x * moveSpeed;
        player.velocity.z = dir.z * moveSpeed;
    }
    else
    {
        player.velocity.x = 0;
        player.velocity.z = 0;
    }

    // ===== d—Íˆ— =====
    if (!player.isGrounded)
    {
        player.velocity.y += player.gravity * dt;

        if (player.velocity.y < player.maxFallSpeed)
            player.velocity.y = player.maxFallSpeed;
    }
    else
    {
        player.velocity.y = 0.0f;
    }
}