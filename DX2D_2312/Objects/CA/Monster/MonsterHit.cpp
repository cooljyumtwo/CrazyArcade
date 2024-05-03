#include "Framework.h"

MonsterHit::MonsterHit(Transform* target, int key, float speed)
{
    SetTarget(target);

    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit_Down.png", 2, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit_Up.png", 2, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit_Right.png", 2, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit_Right.png", 2, 1, true);

    SetMoveSpeed(speed * 0.5f);
}

void MonsterHit::Update()
{
    MonsterMove::Update();

    playHitTime += DELTA;

    if (playHitTime > MAX_HIT_TIME)
    {
        playHitTime -= MAX_HIT_TIME;

        Monster* monster = (Monster*)target;
        monster->SetAction(monster->curType);
        monster->PlusHp();

        if (!Audio::Get()->IsPlaySound("MonsterChangeIdle"))
        {
            Audio::Get()->Play("MonsterChangeIdle");
        }
    }
}
