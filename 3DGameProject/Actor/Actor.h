#pragma once
#include <memory>
#include "../GameObject/GameObject.h"
#include "../Vec3/Vec3.h"

class Actor : public GameObject
{
public:
    Vec3 position{};
    Vec3 rotation{};
    Vec3 scale{ 1,1,1 };
    Vec3 velocity{};

    bool isAlive = true;

    virtual ~Actor() = default;
};