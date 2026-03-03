#pragma once
#include "../../Vec3/Vec3.h"

struct EnemyBlackboard
{
    Vec3 pos{};
    Vec3 velocity{};   // š AI‚ª‚±‚±‚ÉˆÚ“®‘¬“x‚ğ‘‚­

    //Vec3 moveDir{};
    
    Vec3 playerPos{};
    Vec3 lastHeardPos{};

    float moveSpeed = 200.0f;

    float viewRange = 600.0f;
    float viewAngle = 60.0f;
    float hearRange = 400.0f;

    float timer = 0.0f;

    bool canSeePlayer = false;
    bool canHearPlayer = false;
    bool playerMadeSound = false;
};
