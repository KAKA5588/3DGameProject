#include "DxLib.h"
#include <vector>
#include <memory>
#include "../SceneManager/SceneManager.h"
#include "../SceneManager/GameScene.h"
#include "../SceneManager/TitleScene.h"

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

    // デフォルトライトを削除
    while (DeleteLightHandle(0) != -1) {}

    // 念のため全ライト無効化
    SetLightEnable(FALSE);

    // Zバッファなど
    SetDrawScreen(DX_SCREEN_BACK);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    SetDrawScreen(DX_SCREEN_BACK);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    ////  実体を作る
    //Stage stage;
    //Player player;
    //Enemy enemy;
    //Camera camera;

    //camera.SetTarget(&player);
    //player.SetCamera(&camera);
    //player.SetStage(&stage);
    //camera.SetStage(&stage);
    //enemy.SetStage(&stage);

    //std::vector<GameObject*> objects =
    //{
    //    &stage,
    //    &player,
    //    &enemy,
    //    &camera
    //};

    //// Initialize
    //for (auto obj : objects)
    //{
    //    obj->Initialize();
    //}

    SceneManager sceneManager;
    sceneManager.ChangeScene(std::make_unique<TitleScene>());

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();
        float dt = 1.0f / 60.0f;

        sceneManager.Update(dt);
        sceneManager.Draw();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}
