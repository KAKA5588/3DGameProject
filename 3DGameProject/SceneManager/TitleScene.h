#pragma once
#include "Scene.h"
enum class TitleState
{
    Idle,
    FadeOut,
    ShowGolem,
};

class TitleScene : public Scene
{
public:
    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

private:
   int TitleHandle = -1;
   int GolemHandle = -1;

   TitleState state = TitleState::Idle;

   float fadeTime = 0.0f;
   const float fadeDuration = 3.0f;

   // ƒS[ƒŒƒ€•\¦ŠÔ
   float golemTime = 0.0f;
   const float golemDuration = 0.5f;

   int fadeAlpha = 0;
};