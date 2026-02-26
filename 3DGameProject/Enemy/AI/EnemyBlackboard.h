#pragma once
#include "DxLib.h"

struct EnemyBlackboard
{
    VECTOR pos{};
    VECTOR velocity{};

    VECTOR playerPos{};
    VECTOR lastHeardPos{};

    float moveSpeed = 200.0f;

    float viewRange = 600.0f;
    float viewAngle = 60.0f;

    float hearRange = 400.0f;

    float timer = 0.0f;

    bool canSeePlayer = false;
    bool canHearPlayer = false;
    bool playerMadeSound = false;
};