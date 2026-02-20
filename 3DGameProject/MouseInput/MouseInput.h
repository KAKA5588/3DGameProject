#pragma once

class MouseInput
{
public:
    static void Update();

    static float GetDeltaX();
    static float GetDeltaY();

private:
    static float s_deltaX;
    static float s_deltaY;
};
