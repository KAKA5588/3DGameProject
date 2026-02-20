#include "MouseInput.h"
#include <DxLib.h>

float MouseInput::s_deltaX = 0.0f;
float MouseInput::s_deltaY = 0.0f;

void MouseInput::Update()
{
    int screenW, screenH;
    GetDrawScreenSize(&screenW, &screenH);

    int centerX = screenW / 2;
    int centerY = screenH / 2;

    int x, y;
    GetMousePoint(&x, &y);

    // 中心からの差分を取得
    s_deltaX = static_cast<float>(x - centerX);
    s_deltaY = static_cast<float>(y - centerY);

    // マウスを中央に戻す（最重要）
    SetMousePoint(centerX, centerY);
}

float MouseInput::GetDeltaX()
{
    return s_deltaX;
}

float MouseInput::GetDeltaY()
{
    return s_deltaY;
}
