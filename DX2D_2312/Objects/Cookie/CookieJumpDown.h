#pragma once

class CookieJumpDown : public CookieJump
{
public:
    CookieJumpDown(Transform* target);
    
    void Update() override;
    void Start() override;
};