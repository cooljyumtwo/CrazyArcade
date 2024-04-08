#include "Framework.h"

CookieJumpUp::CookieJumpUp(Transform* target)
{
    SetTarget(target);

    LoadClip(PATH, "Cookie_JumpUp.xml", false);
}

void CookieJumpUp::Update()
{
    CookieJump::Update();

    if (velocity.y <= 0.0f)
        Observer::Get()->ExcuteIntEvent("SetAction", Cookie::State::JUMP_DOWN);
}

void CookieJumpUp::Start()
{
    Action::Start();

    velocity = { 0, JUMP_POWER };

    EffectManager::Get()->Play("Fire", target->GetGlobalPosition());
}
