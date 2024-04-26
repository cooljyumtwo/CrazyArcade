#include "Framework.h"

MonsterHit::MonsterHit(Transform* target, int key, float speed)
{
    SetTarget(target);

    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit_Down.png", 2, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit_Up.png", 2, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit_Right.png", 2, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit_Right.png", 2, 1, true);

    SetMoveSpeed(speed * 0.8f);
}
