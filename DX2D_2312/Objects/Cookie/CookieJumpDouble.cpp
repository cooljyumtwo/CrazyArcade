#include "Framework.h"

CookieJumpDouble::CookieJumpDouble(Transform* target)
    : CookieJumpUp(target)
{
    LoadClip(PATH, "Cookie_DoubleJump.xml", false);

    clips[1]->SetEvent(bind(&CookieJumpDouble::EndAction, this));
}

void CookieJumpDouble::Start()
{
    curState = 1;
    clips[1]->Play();

    velocity.y = JUMP_POWER;
}

void CookieJumpDouble::EndAction()
{
    curState = 0;
    clips[0]->Play();
}
