#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
public:
    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

private:

    int bgHandle = -1;

    float fadeTime = 0.0f;
    float fadeDuration = 1.5f;

    int fadeAlpha = 255;
};