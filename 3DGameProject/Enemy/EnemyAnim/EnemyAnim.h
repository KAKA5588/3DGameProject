#pragma once
#include "DxLib.h"
#include <string>
#include <unordered_map>

class EnemyAnim
{
public:
    void Initialize(int modelHandle);
    void Update(float dt);

    void Play(const std::string& name, bool loop = true);

    bool IsFinished() const;

private:
    struct AnimData
    {
        int animHandle; // アニメ用モデル
        int attachNo;   // アタッチ番号
        float time;
        float speed;
        bool loop;
    };

    int modelHandle = -1;


    std::unordered_map<std::string, AnimData> anims;

    std::string currentAnim = "";
};