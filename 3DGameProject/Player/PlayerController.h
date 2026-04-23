#pragma once

class Player;
class Camera;

class PlayerController
{
public:
    void Update(Player& player, Camera* camera, float dt);

private:
    float moveSpeed = 360.0f;
};
