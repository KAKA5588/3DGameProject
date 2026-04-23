#include "UIMouseInput.h"

int UIMouseInput::x = 0;
int UIMouseInput::y = 0;

bool UIMouseInput::prevLeft = false;
bool UIMouseInput::currentLeft = false;

void UIMouseInput::Update()
{
    prevLeft = currentLeft;

    GetMousePoint(&x, &y);

    currentLeft = (GetMouseInput() & MOUSE_INPUT_LEFT);
}

int UIMouseInput::GetX()
{
    return x;
}

int UIMouseInput::GetY()
{
    return y;
}

bool UIMouseInput::IsLeftPressed()
{
    return currentLeft;
}

bool UIMouseInput::IsLeftTriggered()
{
    return currentLeft && !prevLeft;
}