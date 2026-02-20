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

    // ★ コリジョン情報を作成（必須）
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
