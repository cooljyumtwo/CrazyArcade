#include "Framework.h"

CookieRange::CookieRange(Transform* target)
{
    SetTarget(target);

    LoadClip(PATH, "Cookie_Range.xml", false);

    clips[0]->SetEvent(bind(&CookieRange::AttackEnd, this));
    clips[0]->SetEvent(bind(&CookieRange::Fire, this), 2);    
}

void CookieRange::Start()
{
    Action::Start();
    velocity = {};
}

void CookieRange::Fire()
{
    Vector2 direction;

    if (target->GetLocalRotation().y > 0)
        direction.x = -1;
    else
        direction.x = +1;

    Vector2 pos = target->GetGlobalPosition();
    Vector2 clipHalfSize = clips[0]->GetCurFrame()->GetSize() * 0.25f;
    pos += direction * clipHalfSize.x + Vector2::Down() * clipHalfSize.y;

    BulletManager::Get()->Fire("CookieBullet", pos, direction, 10, 300);
    EffectManager::Get()->Play("Hit", pos);
}

void CookieRange::AttackEnd()
{
    Observer::Get()->ExcuteIntEvent("SetAction", Cookie::State::JUMP_DOWN);
}
