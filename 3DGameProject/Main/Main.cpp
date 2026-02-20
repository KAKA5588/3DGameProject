#include "DxLib.h"
#include <vector>

#include "../Stage/Stage.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../GameObject/GameObject.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    SetGraphMode(1920, 1080, 32);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    //  é¿ëÃÇçÏÇÈ
    Stage stage;
    Player player;
    Enemy enemy;
    Camera camera;

    camera.SetTarget(&player);
    player.SetCamera(&camera);
    player.SetStage(&stage);

    std::vector<GameObject*> objects =
    {
        &stage,
        &player,
        &enemy,
        &camera
    };

    // Initialize
    for (auto obj : objects)
    {
        obj->Initialize();
    }

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();
        float dt = 1.0f / 60.0f;

        for (auto obj : objects)
        {
            obj->Update(dt);
        }

        camera.Apply();

        for (auto obj : objects)
        {
            obj->Draw();
        }

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}
