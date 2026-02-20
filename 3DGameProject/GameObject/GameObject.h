#pragma once

class GameObject
{
public:
    virtual ~GameObject() = default;

    virtual void Initialize() {}
    virtual void Update(float dt) {}
    virtual void Draw() {}
};
