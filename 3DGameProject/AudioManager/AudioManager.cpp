#include "AudioManager.h"
#include "DxLib.h"

AudioManager& AudioManager::GetInstance()
{
    static AudioManager instance;
    return instance;
}

void AudioManager::Initialize()
{
    // SEƒ[ƒh
    seHandles[SEType::FootStep] =
        LoadSoundMem("Resource/Audio/SE/‘«‰¹.mp3");

    // BGMƒ[ƒh
    bgmHandles[BGMType::Stage1] =
        LoadSoundMem("Resource/Audio/“ú–v”pZ.mp3");
}

void AudioManager::PlaySE(SEType type)
{
    auto it = seHandles.find(type);
    if (it == seHandles.end()) return;

    if (type == SEType::FootStep)
        PlaySoundMem(it->second, DX_PLAYTYPE_LOOP);  // ‘«‰¹‚Íƒ‹[ƒv
    else
        PlaySoundMem(it->second, DX_PLAYTYPE_BACK);
}

void AudioManager::StopSE(SEType type)
{
    auto it = seHandles.find(type);
    if (it == seHandles.end()) return;

    StopSoundMem(it->second);
}

void AudioManager::PlayBGM(BGMType type)
{
    auto it = bgmHandles.find(type);
    if (it == bgmHandles.end()) return;

    if (currentBGM != -1)
    {
        StopSoundMem(currentBGM);
    }

    currentBGM = it->second;
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