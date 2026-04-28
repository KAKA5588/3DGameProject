#pragma once
#include <unordered_map>

enum class SEType
{
    EnemyDead,
    FootStep,
};

enum class SECategory
{
    FootStep,
    Battle,
    System,
};

enum class BGMType
{
    TitleSceneBGM,
    GamaSceneBGM,


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

    // ======================
    // 音量（カテゴリ別SE + BGM）
    // ======================
    void SetSEVolume(SECategory category, int volume); // 0～255
    void SetBGMVolume(int volume);

    int GetSEVolume(SECategory category) const;
    int GetBGMVolume() const { return bgmVolume; }

private:
    AudioManager() = default;

    struct SEData
    {
        int handle = -1;
        int volume = 255;
        SECategory category;
    };

    std::unordered_map<SEType, SEData> seData;
    std::unordered_map<BGMType, int> bgmHandles;

    std::unordered_map<SECategory, int> seCategoryVolume;

    int currentBGM = -1;
    int bgmVolume = 255;
};