#include "Framework.h"

void CookieJump::Update()
{
    velocity.y -= GRAVITY * DELTA;
    target->Translate(Vector2::Up() * velocity.y * DELTA);

    Move();

    Action::Update();
}

bool CookieJump::IsCollisionFloor()
{
    RectCollider* cookie = ((Cookie*)target)->GetCollider();
    RectCollider* floor = FloorManager::Get()->Collision(cookie);

    if (floor == nullptr) return false;

    float cookieBottom = cookie->RightBottom().y;
    float floorTop = floor->RightTop().y;    

    if (cookieBottom < floorTop && cookieBottom > floorTop - FLOOR_EPSILON)
    {
        target->Translate(Vector2::Up() * (floorTop - cookieBottom));
        return true;
    }

    return false;
}
