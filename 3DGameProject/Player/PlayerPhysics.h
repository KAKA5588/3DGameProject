#pragma once
#include "../Vec3/Vec3.h"   

class Player;
class Stage;

class PlayerPhysics
{
public:
    void Update(Player& player, Stage* stage, float dt);

private:
    float radius = 10.0f;
    

    void ApplyGravity(Player& player, float dt);
    void ResolveFloor(Player& player, Stage* stage, Vec3& nextPos);
    void ResolveWall(Player& player, Stage* stage, Vec3& nextPos);
};
