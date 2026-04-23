#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

private:
   int TitleHandle = -1;


};