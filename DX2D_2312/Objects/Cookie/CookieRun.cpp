#include "Framework.h"

CookieRun::CookieRun(Transform* target)    
{
    SetTarget(target);

    LoadClip(PATH, "Cookie_Run.xml", true);
}

void CookieRun::Update()
{
    CookieJump::Update();

    RectCollider* cookie = ((Cookie*)target)->GetCollider();
    target->UpdateWorld();
    cookie->UpdateWorld();

    if (IsCollisionFloor())
    {
        velocity.y = 0.0f;
    }
    else
    {
        Observer::Get()->ExcuteIntEvent("SetAction", Cookie::State::JUMP_DOWN);
    }
}