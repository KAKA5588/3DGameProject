#pragma once
#include "../../Vec3/Vec3.h"

struct EnemyBlackboard
{
    Vec3 pos{};// 敵の現在位   
    Vec3 velocity{}; // AIが決定する移動速度  
    Vec3 forward{};// 敵が向いている方向（視野判定や索敵移動に使用）
    Vec3 playerPos{};// プレイヤーの現在位置   
    Vec3 lastHeardPos{}; // 最後に音を聞いた位置
   
    float moveSpeed = 100.0f; // 移動速度   

    float viewRange = 900.0f;// 視覚の感知距離    

    float viewAngle = 120.0f; // 視野角  

    float hearRange = 400.0f; // 聴覚の感知距離
  
    float timer = 0.0f;// 状態管理用タイマー  

    float lostTimer = 0.0f;// 見失い時間計測用   

    float lostTimeLimit = 3.0f;// 見失い後に索敵へ戻るまでの時間
    
    bool canSeePlayer = false;// 視界内にいるか  

    bool canHearPlayer = false;// 音を感知しているか

    bool playerMadeSound = false;// プレイヤーが音を出しているか

    bool hitWall = false;// 壁に衝突したか

    //************************************
    //壁判定を後回しにするので止まっていたら向きを変える
    //float stuckTimer = 0.0f;   // 動いていない時間
};