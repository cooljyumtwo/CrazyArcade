#include "Framework.h"

CookieJumpDown::CookieJumpDown(Transform* target)
{
    SetTarget(target);

    LoadClip(PATH, "Cookie_JumpDown.xml", false);
}

void CookieJumpDown::Update()
{
    CookieJump::Update();
    
    if (IsCollisionFloor())
    {
        Observer::Get()->ExcuteEvent("Landing");
        EffectManager::Get()->Play("Fire2", target->GetGlobalPosition());
    }    
}

void CookieJumpDown::Start()
{
    Action::Start();
    velocity.y = 0.0f;
}
