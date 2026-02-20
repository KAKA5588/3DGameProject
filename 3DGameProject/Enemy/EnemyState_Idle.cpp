#include "EnemyState_Idle.h"
#include "Enemy.h"
#include <DxLib.h>

void EnemyState_Idle::Initialize(Enemy*)
{
    printfDx("[Enemy] Enter Idle State\n");
}

void EnemyState_Idle::Update(Enemy*, float)
{
    // 今は何もしない（後で探索・検知を入れる）
}

void EnemyState_Idle::Terminate(Enemy*)
{
    printfDx("[Enemy] Exit Idle State\n");
}
