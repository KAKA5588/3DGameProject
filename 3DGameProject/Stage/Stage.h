#include "../GameObject/GameObject.h"

class Stage : public GameObject
{
public:
    Stage();
    ~Stage();

    //唯一のインスタンスの取得
    static Stage* Instance()
    {
        static Stage instance;
        return &instance;
    }

    void Initialize() override;
    void Update(float dt) override; // ← これだけでOK
    void Draw() override;

    int GetModelHandle() const { return Stage_handle; }

private:
    int Stage_handle = -1;
};
