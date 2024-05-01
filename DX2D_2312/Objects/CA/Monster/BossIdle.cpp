#include "Framework.h"

BossIdle::BossIdle(Transform* target, int key, int max_frameX)
{
    SetTarget(target);

    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Idle.png", max_frameX, 1, true);
}