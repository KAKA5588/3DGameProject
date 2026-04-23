#pragma once
#include <unordered_map>

enum class SEType
{
    EnemyDead,
    FootStep,
};

enum class BGMType
{
    Stage1,
};

class AudioManager
{
public:
    static AudioManager& GetInstance();

    void Initialize();
    void PlaySE(SEType type);
    void StopSE(SEType type);

    void PlayBGM(BGMType type);
    void StopBGM();

private:
    AudioManager() = default;

    std::unordered_map<SEType, int> seHandles;
    std::unordered_map<BGMType, int> bgmHandles;

    int currentBGM = -1;
};