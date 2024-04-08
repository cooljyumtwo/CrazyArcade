#pragma once

class CookieJumpUp : public CookieJump
{
public:
    CookieJumpUp(Transform* target);

    void Update() override;
    void Start() override;
};