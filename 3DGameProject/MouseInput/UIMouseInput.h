#pragma once
#include "DxLib.h"

class UIMouseInput
{
public:
    static void Update();

    static int GetX();
    static int GetY();

    static bool IsLeftPressed();   // ‰Ÿ‚µ‚Ä‚¢‚é
    static bool IsLeftTriggered(); // ‰Ÿ‚µ‚½uŠÔ

private:
    static int x;
    static int y;

    static bool prevLeft;
    static bool currentLeft;
};