#include "DxLib.h"
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
    if (Stage_handle != -1)
    {
        MV1DeleteModel(Stage_handle);
        Stage_handle = -1;
    }
}

void Stage::Initialize()
{
    Stage_handle = MV1LoadModel("Resource/Stage/Stage_Obj018.mv1");
    if (Stage_handle == -1)
    {
        printfDx("ステージモデルの読み込み失敗\n");
        return;
    }

    // ===== COLOR_F を作る =====
    COLOR_F black;
    black.r = 0.0f;
    black.g = 0.0f;
    black.b = 0.0f;
    black.a = 1.0f;

    COLOR_F dark;
    dark.r = 0.2f;
    dark.g = 0.2f;
    dark.b = 0.2f;
    dark.a = 1.0f;

    // ===== 自己発光を消す =====
    MV1SetMaterialEmiColor(Stage_handle, -1, black);

    // ===== ディフューズを暗く =====
    MV1SetMaterialDifColor(Stage_handle, -1, dark);

    // コリジョン
    MV1SetupCollInfo(Stage_handle, -1, 8, 8, 8);
}

void Stage::Update(float dt)
{
    // ステージは毎フレーム処理がなければ空でOK
}


void Stage::Draw()
{
    if (Stage_handle != -1)
    {
        MV1DrawModel(Stage_handle);
    }
}
