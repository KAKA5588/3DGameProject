#include "EnemyAnim.h"

void EnemyAnim::Initialize(int handle)
{
    modelHandle = handle;

    // ===== アニメモデル読み込み =====
    int walkModel = MV1LoadModel("Resource/Enemy/Anim_Walk.mv1");
    int attackModel = MV1LoadModel("Resource/Enemy/Anim_Attack3.mv1");

    anims["Walk"] =
    {
        walkModel,
        -1,
        0.0f,
        10.0f,
        true
    };

    anims["Attack"] =
    {
        attackModel,
        -1,
        0.0f,
        10.0f,
        false
    };
}

void EnemyAnim::Play(const std::string& name, bool loop)
{
    if (currentAnim == name) return;

    // 既存アニメ削除
    if (!currentAnim.empty())
    {
        auto& oldAnim = anims[currentAnim];
        MV1DetachAnim(modelHandle, oldAnim.attachNo);
    }

    currentAnim = name;

    auto& anim = anims[name];
    anim.time = 0.0f;
    anim.loop = loop;

    // ★ 外部アニメをアタッチ
    anim.attachNo = MV1AttachAnim(
        modelHandle,
        0,
        anim.animHandle,
        FALSE
    );
}

void EnemyAnim::Update(float dt)
{
    if (currentAnim.empty()) return;

    auto& anim = anims[currentAnim];

    anim.time += dt * anim.speed;

    float totalTime = MV1GetAnimTotalTime(anim.animHandle, 0);

    if (anim.loop)
    {
        if (anim.time > totalTime)
        {
            anim.time = fmod(anim.time, totalTime);
        }
    }
    else
    {
        if (anim.time > totalTime)
        {
            anim.time = totalTime;
        }
    }

    MV1SetAttachAnimTime(modelHandle, anim.attachNo, anim.time);
}

bool EnemyAnim::IsFinished() const
{
    if (currentAnim.empty()) return true;

    const auto& anim = anims.at(currentAnim);
    float totalTime = MV1GetAnimTotalTime(anim.animHandle, 0);

    return !anim.loop && anim.time >= totalTime;
}