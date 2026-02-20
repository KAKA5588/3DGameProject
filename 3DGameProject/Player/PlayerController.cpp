#include "PlayerController.h"
#include "Player.h"
#include "../Camera/Camera.h"
#include "DxLib.h"
#include <cmath>

void PlayerController::Update(Player& player, Camera* camera)
{
    if (!camera) return;

    Vec3 input{ 0,0,0 };

    if (CheckHitKey(KEY_INPUT_W)) input.z += 1;
    if (CheckHitKey(KEY_INPUT_S)) input.z -= 1;
    if (CheckHitKey(KEY_INPUT_A)) input.x -= 1;
    if (CheckHitKey(KEY_INPUT_D)) input.x += 1;

    if (input.x == 0 && input.z == 0)
    {
        player.velocity.x = 0;
        player.velocity.z = 0;
        return;
    }

    float yaw = camera->GetYaw();

    Vec3 forward{ sinf(yaw), 0.0f, cosf(yaw) };
    Vec3 right{ cosf(yaw), 0.0f, -sinf(yaw) };

    Vec3 dir = forward * input.z + right * input.x;

    float len = sqrtf(dir.x * dir.x + dir.z * dir.z);
    if (len > 0.0f)
    {
        dir.x /= len;
        dir.z /= len;
    }

    player.velocity.x = dir.x * moveSpeed;
    player.velocity.z = dir.z * moveSpeed;
}
