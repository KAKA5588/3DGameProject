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

public:
    bool IsMakingNoise() const { return isMakingNoise; }
    float GetNoiseStrength() const { return noiseStrength; }
    //ターゲット
    const VECTOR& GetPosition() const { return position; }

private:
    bool isMakingNoise = false;
    float noiseStrength = 0.0f;

private:
    Stage* stage = nullptr;
    Camera* camera = nullptr;

    std::unique_ptr<PlayerController> controller;
    std::unique_ptr<PlayerPhysics> physics;

    int modelHandle = -1;
};
