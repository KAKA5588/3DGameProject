#include "AudioManager.h"
#include "DxLib.h"

AudioManager& AudioManager::GetInstance()
{
    static AudioManager instance;
    return instance;
}

// ======================
// èâä˙âª
// ======================
void AudioManager::Initialize()
{
    // SEìoò^
    seData[SEType::FootStep] =
    {
        LoadSoundMem("Resource/Audio/SE/ìyÇÃè„Çï‡Ç≠.mp3"),
        255,
        SECategory::FootStep
    };

    seData[SEType::EnemyDead] =
    {
        LoadSoundMem("Resource/Audio/SE/ìGéÄñS.mp3"),
        255,
        SECategory::Battle
    };

    // BGM
    bgmHandles[BGMType::GamaSceneBGM] =
        LoadSoundMem("Resource/Audio/ì˙ñvîpçZ.mp3");

    bgmHandles[BGMType::TitleSceneBGM] =
        LoadSoundMem("Resource/Audio/ã^òfÇÃñ∂.mp3");

    // ÉfÉtÉHÉãÉgâπó 
    seCategoryVolume[SECategory::FootStep] = 255;
    seCategoryVolume[SECategory::Battle] = 255;
    seCategoryVolume[SECategory::System] = 255;
}

// ======================
// SEçƒê∂
// ======================
void AudioManager::PlaySE(SEType type)
{
    auto it = seData.find(type);
    if (it == seData.end()) return;

    SEData& data = it->second;

    int volume = seCategoryVolume[data.category];

    ChangeVolumeSoundMem(volume, data.handle);
    PlaySoundMem(data.handle, DX_PLAYTYPE_BACK);
}

void AudioManager::StopSE(SEType type)
{
    auto it = seData.find(type);
    if (it == seData.end()) return;

    StopSoundMem(it->second.handle);
}

// ======================
// BGM
// ======================
void AudioManager::PlayBGM(BGMType type)
{
    auto it = bgmHandles.find(type);
    if (it == bgmHandles.end()) return;

    if (currentBGM != -1)
        StopSoundMem(currentBGM);

    currentBGM = it->second;

    ChangeVolumeSoundMem(bgmVolume, currentBGM);
    PlaySoundMem(currentBGM, DX_PLAYTYPE_LOOP);
}

void AudioManager::StopBGM()
{
    if (currentBGM != -1)
    {
        StopSoundMem(currentBGM);
        currentBGM = -1;
    }
}

// ======================
// SEâπó ÅiÉJÉeÉSÉäï Åj
// ======================
void AudioManager::SetSEVolume(SECategory category, int volume)
{
    if (volume < 0) volume = 0;
    if (volume > 255) volume = 255;

    seCategoryVolume[category] = volume;
}

int AudioManager::GetSEVolume(SECategory category) const
{
    auto it = seCategoryVolume.find(category);
    if (it == seCategoryVolume.end()) return 255;

    return it->second;
}

// ======================
// BGMâπó 
// ======================
void AudioManager::SetBGMVolume(int volume)
{
    if (volume < 0) volume = 0;
    if (volume > 255) volume = 255;

    bgmVolume = volume;

    if (currentBGM != -1)
    {
        ChangeVolumeSoundMem(bgmVolume, currentBGM);
    }
}