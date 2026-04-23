#pragma once
#include "Scene.h"
#include <vector>
#include <memory>

#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Camera/Camera.h"
#include "../GameObject/GameObject.h"

class GameScene : public Scene
{
public:
    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

    ~GameScene();

private:
    // 所有する（寿命管理する）
    std::unique_ptr<Stage> stage;
    std::unique_ptr<Player> player;
    std::unique_ptr<Enemy> enemy;
    std::unique_ptr<Camera> camera;

    // 参照だけ（所有しない）
    std::vector<GameObject*> objects;
};