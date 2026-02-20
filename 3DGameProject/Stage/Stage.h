#include "../GameObject/GameObject.h"

class Stage : public GameObject
{
public:
    Stage();
    ~Stage();

    void Initialize() override;
    void Update(float dt) override; // Å© Ç±ÇÍÇæÇØÇ≈OK
    void Draw() override;

    int GetModelHandle() const { return Stage_handle; }

private:
    int Stage_handle = -1;
};
