// Player.h
#pragma once
#include "../Actor/Actor.h"
#include <memory>

class Stage;
class Camera;
class PlayerController;
class PlayerPhysics;

class Player : public Actor
{
public:
    Player();
    ~Player();

    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

    void SetStage(Stage* s);
    void SetCamera(Camera* cam);

    bool isGrounded = false;

private:
    Stage* stage = nullptr;
    Camera* camera = nullptr;

    std::unique_ptr<PlayerController> controller;
    std::unique_ptr<PlayerPhysics> physics;

    int modelHandle = -1;
};
